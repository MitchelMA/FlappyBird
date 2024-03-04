#include "PipeObstacle.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

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
	const auto HalfGapHeight = GapHeight / 2;
	const auto TotalHeight = TopBoxHeight + BottomBoxHeight + GapHeight;

	DefaultSceneRoot->SetRelativeLocation({0, 5, HeightOffset});

	TopCollisionBox->SetRelativeLocation({0, 0, TopBoxHeight + HalfGapHeight});
	BottomCollisionBox->SetRelativeLocation({0, 0, -BottomBoxHeight - HalfGapHeight});
	
	PassCollisionBox->SetRelativeLocation({GetPassBarrierXPosition(), 0, 0});
	PassCollisionBox->SetBoxExtent({5, TotalHeight, 5});
		
}

APipeObstacle::APipeObstacle()
{
	// Enables the Tick function
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->Mobility = EComponentMobility::Movable;
	DefaultSceneRoot->SetupAttachment(RootComponent);
	
	TopCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TopCollision"));
	TopCollisionBox->Mobility = EComponentMobility::Movable;
	TopCollisionBox->SetupAttachment(DefaultSceneRoot);
	
	BottomCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomCollision"));
	BottomCollisionBox->Mobility = EComponentMobility::Movable;
	BottomCollisionBox->SetupAttachment(DefaultSceneRoot);
	
	TopPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TopPanel"));
	TopPanel->Mobility = EComponentMobility::Movable;
	TopPanel->SetupAttachment(TopCollisionBox);
	
	BottomPanel = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BottomPanel"));
	BottomPanel->Mobility = EComponentMobility::Movable;
	BottomPanel->SetupAttachment(BottomCollisionBox);

	PassCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PassCollisionBox"));
	PassCollisionBox->Mobility = EComponentMobility::Movable;
	PassCollisionBox->SetupAttachment(DefaultSceneRoot);

	SetTopSpriteSource(TopSpriteSource);
	SetBottomSpriteSource(BottomSpriteSource);
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
	const auto WidestExtent = fmax(TopCollisionBox->GetScaledBoxExtent()[2],
		BottomCollisionBox->GetScaledBoxExtent()[2]);
	const auto XDirection = -DirectionMultiplier[0];
	const auto PassBarrierWidth = PassCollisionBox->GetScaledBoxExtent()[1];

	return (WidestExtent + PassBarrierWidth) * XDirection;
}
