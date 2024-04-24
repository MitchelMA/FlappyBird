#include "PipeObstacle.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "ScoreSpeedComponent.h"

#if WITH_EDITOR

void
APipeObstacle::PostEditChangeProperty(
	FPropertyChangedEvent& PropertyChangedEvent
)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APipeObstacle, TopSpriteSource) && TopPanel != nullptr)
		SetTopSpriteSource(TopSpriteSource);

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APipeObstacle, BottomSpriteSource) && BottomPanel != nullptr)
		SetBottomSpriteSource(BottomSpriteSource);

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APipeObstacle, bMirrorTop))
		SetMirrorsTop(bMirrorTop);

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APipeObstacle, GapHeight))
		SetGapHeight(GapHeight);

	if (PropertyName == GET_MEMBER_NAME_CHECKED(APipeObstacle, HeightOffset))
		SetHeightOffset(HeightOffset);
}

#endif // WITH_EDITOR

void APipeObstacle::BeginPlay()
{
	Super::BeginPlay();

	const auto [TopExtend, BottomExtend] = GetPipeExtends();
	const auto TopBoxHeight = TopExtend[2];
	const auto BottomBoxHeight = BottomExtend[2];
	const auto TotalHeight = TopBoxHeight + BottomBoxHeight + GapHeight/2;

	SetGapHeight(GapHeight);
	SetHeightOffset(HeightOffset);
	
	PassCollisionBox->SetBoxExtent({10, 10, TotalHeight});
	PassCollisionBox->SetRelativeLocation({GetPassBarrierXPosition(), 0, 0});
}

TPair<UE::Math::TVector<double>, UE::Math::TVector<double>>
APipeObstacle::GetPipeExtends()
const noexcept
{
	const auto TopExtend = TopPanel->Bounds.GetBox().GetExtent();
	const auto BottomExtend = BottomPanel->Bounds.GetBox().GetExtent();
	
	return {TopExtend, BottomExtend};
}

TPair<UE::Math::TVector<double>, UE::Math::TVector<double>>
APipeObstacle::GetPipeSizes()
const noexcept
{
	const auto TopSize = TopPanel->Bounds.GetBox().GetSize();
	const auto BottomSize = BottomPanel->Bounds.GetBox().GetSize();

	return {TopSize, BottomSize};
}

APipeObstacle::APipeObstacle()
{
	// Enables the Tick function
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->Mobility = EComponentMobility::Movable;
	RootComponent = DefaultSceneRoot;

	PipesOffset = CreateDefaultSubobject<USceneComponent>(TEXT("PipesOffset"));
	PipesOffset->Mobility = EComponentMobility::Movable;
	PipesOffset->SetupAttachment(DefaultSceneRoot);
	
	TopPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopPanel"));
	TopPanel->Mobility = EComponentMobility::Movable;
	TopPanel->SetupAttachment(PipesOffset);
	
	BottomPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomPanel"));
	BottomPanel->Mobility = EComponentMobility::Movable;
	BottomPanel->SetupAttachment(PipesOffset);

	PassCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PassCollisionBox"));
	PassCollisionBox->Mobility = EComponentMobility::Movable;
	PassCollisionBox->SetupAttachment(DefaultSceneRoot);

	SpeedComponent = Cast<USpeedComponent>(CreateDefaultSubobject<UScoreSpeedComponent>(TEXT("SpeedComponent")));

	SetTopSpriteSource(TopSpriteSource);
	SetBottomSpriteSource(BottomSpriteSource);

	// disables overlap events (they are heavy for moving targets);
	FCollisionResponseContainer CollisionResponses = FCollisionResponseContainer();
	CollisionResponses.SetAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionResponses.SetResponse(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	
	TopPanel->SetGenerateOverlapEvents(false);
	TopPanel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TopPanel->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	TopPanel->SetCollisionResponseToChannels(CollisionResponses);
	
	BottomPanel->SetGenerateOverlapEvents(false);
	BottomPanel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BottomPanel->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BottomPanel->SetCollisionResponseToChannels(CollisionResponses);
}

void
APipeObstacle::Tick(
	const float DeltaSeconds
)
{
	Super::Tick(DeltaSeconds);

	auto CurrentPosition = GetActorLocation();
	auto Direction = DirectionMultiplier * SpeedComponent->GetSpeed() * DeltaSeconds;
	CurrentPosition += {Direction[0], 0, Direction[1]};

	SetActorLocation(CurrentPosition);
}

void
APipeObstacle::SetTopSpriteSource(
	UPaperSprite* NewSpriteSource
)
{
	if (IsValid(TopPanel))
		TopPanel->SetSprite(NewSpriteSource);

	if (!bMirrorTop || !IsValid(BottomPanel))
		return;

	TopSpriteSource = NewSpriteSource;
	BottomSpriteSource = NewSpriteSource;
	BottomPanel->SetSprite(NewSpriteSource);

	const auto TopPanelRot = TopPanel->GetRelativeRotation();
	const FRotator RotationAddition = {0, 0, 180};
	
	BottomPanel->SetRelativeRotation(TopPanelRot + RotationAddition);
}

void
APipeObstacle::SetBottomSpriteSource(
	UPaperSprite* NewSpriteSource
)
{
	if (!IsValid(BottomPanel) || bMirrorTop)
		return;

	BottomSpriteSource = NewSpriteSource;
	BottomPanel->SetSprite(NewSpriteSource);
}

void
APipeObstacle::SetMirrorsTop(
	const bool NewValue
)
{
	bMirrorTop = NewValue;
	
	SetTopSpriteSource(TopSpriteSource);
	SetBottomSpriteSource(BottomSpriteSource);
}

double
APipeObstacle::GetPassBarrierXPosition()
const
{
	const auto [TopExtend, BottomExtend] = GetPipeExtends();
	const auto WidestExtent = fmax(TopExtend[0], BottomExtend[0]);
	const auto XDirection = -DirectionMultiplier[0];
	const auto PassBarrierWidth = PassCollisionBox->GetScaledBoxExtent()[0];

	return (WidestExtent + PassBarrierWidth/2) * XDirection;
}

void
APipeObstacle::SetGapHeight(
	const float NewGapHeight
)
{
	GapHeight = NewGapHeight;

	const auto [TopExtend, BottomExtend] = GetPipeExtends();
	const auto TopBoxHeight = TopExtend[2];
	const auto BottomBoxHeight = BottomExtend[2];
	const auto HalfGapHeight = GapHeight / 2;

	TopPanel->SetRelativeLocation({0, 0, TopBoxHeight + HalfGapHeight});
	BottomPanel->SetRelativeLocation({0, 0, -BottomBoxHeight - HalfGapHeight});
}

void
APipeObstacle::SetHeightOffset(
	const float NewHeightOffset
)
{
	HeightOffset = NewHeightOffset;
	PipesOffset->SetRelativeLocation({0, 5, HeightOffset});
}
