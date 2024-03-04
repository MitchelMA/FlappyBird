#include "PipeObstacle.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "ScoreSpeedComponent.h"

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
}

void APipeObstacle::BeginPlay()
{
	Super::BeginPlay();

	const auto TopBoxHeight = TopCollisionBox->GetScaledBoxExtent()[2];
	const auto BottomBoxHeight = BottomCollisionBox->GetScaledBoxExtent()[2];
	const auto TotalHeight = TopBoxHeight + BottomBoxHeight + GapHeight;

	SetGapHeight(GapHeight);
	SetHeightOffset(HeightOffset);
	
	PassCollisionBox->SetBoxExtent({5, TotalHeight, 5});
	PassCollisionBox->SetRelativeLocation({GetPassBarrierXPosition(), 0, 0});
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
	
	TopCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopCollision"));
	TopCollisionBox->Mobility = EComponentMobility::Movable;
	TopCollisionBox->SetupAttachment(PipesOffset);
	
	BottomCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomCollision"));
	BottomCollisionBox->Mobility = EComponentMobility::Movable;
	BottomCollisionBox->SetupAttachment(PipesOffset);
	
	TopPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopPanel"));
	TopPanel->Mobility = EComponentMobility::Movable;
	TopPanel->SetupAttachment(TopCollisionBox);
	
	BottomPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomPanel"));
	BottomPanel->Mobility = EComponentMobility::Movable;
	BottomPanel->SetupAttachment(BottomCollisionBox);

	PassCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PassCollisionBox"));
	PassCollisionBox->Mobility = EComponentMobility::Movable;
	PassCollisionBox->SetupAttachment(DefaultSceneRoot);

	SpeedComponent = Cast<USpeedComponent>(CreateDefaultSubobject<UScoreSpeedComponent>(TEXT("SpeedComponent")));

	SetTopSpriteSource(TopSpriteSource);
	SetBottomSpriteSource(BottomSpriteSource);
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
	if (TopPanel != nullptr)
		TopPanel->SetSprite(NewSpriteSource);

	if (!bMirrorTop || BottomPanel == nullptr)
		return;
	
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
	if (BottomPanel == nullptr || bMirrorTop)
		return;

	BottomPanel->SetSprite(NewSpriteSource);
}

double
APipeObstacle::GetPassBarrierXPosition()
const
{
	const auto WidestExtent = fmax(TopCollisionBox->GetScaledBoxExtent()[0],
		BottomCollisionBox->GetScaledBoxExtent()[0]);
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
	
	const auto TopBoxHeight = TopCollisionBox->GetScaledBoxExtent()[2];
	const auto BottomBoxHeight = BottomCollisionBox->GetScaledBoxExtent()[2];
	const auto HalfGapHeight = GapHeight / 2;


	TopCollisionBox->SetRelativeLocation({0, 0, TopBoxHeight + HalfGapHeight});
	BottomCollisionBox->SetRelativeLocation({0, 0, -BottomBoxHeight - HalfGapHeight});
}

void
APipeObstacle::SetHeightOffset(
	const float NewHeightOffset
)
{
	HeightOffset = NewHeightOffset;
	PipesOffset->SetRelativeLocation({0, 5, HeightOffset});
}
