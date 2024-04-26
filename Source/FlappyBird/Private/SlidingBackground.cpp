#include "SlidingBackground.h"
#include "ScoreSpeedComponent.h"

// Sets default values
ASlidingBackground::ASlidingBackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	PanelOffset = CreateDefaultSubobject<USceneComponent>(TEXT("Panel Offset"));
	PanelOffset->SetupAttachment(DefaultSceneRoot);

	PanelZero = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_0"));
	PanelZero->Mobility = EComponentMobility::Movable;
	PanelZero->SetupAttachment(PanelOffset);
	PanelZero->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	PanelOne = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_1"));
	PanelOne->Mobility = EComponentMobility::Movable;
	PanelOne->SetupAttachment(PanelOffset);
	PanelOne->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpeedComponent = Cast<USpeedComponent>(CreateDefaultSubobject<UScoreSpeedComponent>(TEXT("SpeedComponent")));

	PanelZero->SetGenerateOverlapEvents(false);
	PanelZero->SetCollisionProfileName(TEXT("NoCollision"));
	PanelOne->SetGenerateOverlapEvents(false);
	PanelOne->SetCollisionProfileName(TEXT("NoCollision"));

	SetBackgroundSource(BackgroundSource);
}

#if WITH_EDITOR

void
ASlidingBackground::PostEditChangeProperty(
	FPropertyChangedEvent& e
)
{
	Super::PostEditChangeProperty(e);

	const auto PropertyName = e.Property != nullptr ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASlidingBackground, BackgroundSource))
		SetBackgroundSource(BackgroundSource);
}

#endif // WITH_EDITOR

// Called when the game starts or when spawned
void
ASlidingBackground::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void
ASlidingBackground::Tick(
	const float DeltaTime
)
{
	Super::Tick(DeltaTime);

	const auto NextXOffset = PanelOffset->GetRelativeLocation()[0] + DeltaTime * HorizontalDirectionMultiplier * SpeedComponent->GetSpeed();
	Progression = fabs(NextXOffset) / GetPanelSize()[0];
	Progression = fmod(Progression, 1);

	SetProgression(Progression);
}


void
ASlidingBackground::SetBackgroundSource(
	UPaperSprite* NewSource
)
{
	if (!IsValid(PanelZero) || !IsValid(PanelOne))
		return;

	BackgroundSource = NewSource;
	PanelZero->SetSprite(BackgroundSource);
	PanelOne->SetSprite(BackgroundSource);

	const auto PanelZeroPos = PanelZero->GetRelativeLocation();
	const auto XOffset = GetPanelSize()[0] * -HorizontalDirectionMultiplier;
	PanelOne->SetRelativeLocation({PanelZeroPos[0] + XOffset, PanelZeroPos[1], PanelZeroPos[2]});
	

	// reset the current progression
	SetProgression(0);
}

void
ASlidingBackground::SetProgression(
	const float NewProgression
)
{
	if (!IsValid(PanelZero) || !IsValid(PanelOne))
		return;
	
	Progression = NewProgression;
	const auto PanelSize = GetPanelSize();
	const auto CurrentPanelPos = PanelOffset->GetRelativeLocation();
	const auto Offset = PanelSize[0] * HorizontalDirectionMultiplier * Progression;

	PanelOffset->SetRelativeLocation({Offset, CurrentPanelPos[1], CurrentPanelPos[2]});
}

void
ASlidingBackground::SetDirectionMultiplier(
	const float NewDirectionMultiplier
)
{
	HorizontalDirectionMultiplier = NewDirectionMultiplier;
	SetProgression(Progression);
}
