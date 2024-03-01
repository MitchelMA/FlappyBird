// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingBackground.h"

// Sets default values
ASlidingBackground::ASlidingBackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PanelZero = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_0"));
	PanelZero->Mobility = EComponentMobility::Movable;
	
	PanelOne = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_1"));
	PanelOne->Mobility = EComponentMobility::Movable;

	SetBackgroundSource(BackgroundSource);
}

void ASlidingBackground::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	auto propertyName = e.Property != nullptr ? e.Property->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(ASlidingBackground, BackgroundSource))
		SetBackgroundSource(BackgroundSource);
}


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
	
	Progression += DeltaTime * SlideSpeed;
	Progression = fmod(Progression, 1);

	SetProgression(Progression);
}


void
ASlidingBackground::SetBackgroundSource(
	UPaperSprite* NewSource
)
{
	if (PanelZero == nullptr || PanelOne == nullptr)
		return;

	BackgroundSource = NewSource;
	PanelZero->SetSprite(BackgroundSource);
	PanelOne->SetSprite(BackgroundSource);

	// reset the current progression
	SetProgression(0);
}

void
ASlidingBackground::SetProgression(
	const float NewProgression
)
{
	if (PanelZero == nullptr || PanelOne == nullptr)
		return;
	
	Progression = NewProgression;
	
	auto dimensions = GetPanelSize();
	auto yPos = PanelZero->GetRelativeLocation()[1];
	auto baseOffset = dimensions * DirectionMultiplier;
	
	auto offsetPanelZero = baseOffset * Progression;
	auto offsetPanelOne = baseOffset * Progression - baseOffset;
	
	PanelZero->SetRelativeLocation({offsetPanelZero[0], yPos, offsetPanelZero[1]});
	PanelOne->SetRelativeLocation({offsetPanelOne[0], yPos, offsetPanelOne[1]});
}

void
ASlidingBackground::SetDirectionMultiplier(
	const FVector2D NewDirectionMultiplier
)
{
	DirectionMultiplier = NewDirectionMultiplier;
	SetProgression(Progression);
}
