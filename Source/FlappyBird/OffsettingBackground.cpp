// Fill out your copyright notice in the Description page of Project Settings.

#include "OffsettingBackground.h"

#include "PaperSprite.h"

AOffsettingBackground::AOffsettingBackground(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	// default speed
	SlideSpeed = 0.1f;

	PanelZero = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_0"));
	PanelZero->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	PanelZero->Mobility = EComponentMobility::Static;

	PanelOne = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Panel_1"));
	PanelOne->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	PanelOne->Mobility = EComponentMobility::Static;
}

void AOffsettingBackground::BeginPlay()
{
	auto val = PrimaryActorTick.IsTickFunctionRegistered();
	if (auto sprite = PanelZero->GetSprite())
	{
		Width = sprite->GetSourceSize()[0];
	}
	else { Width = 0; }
}

void AOffsettingBackground::Tick(
	float DeltaSeconds
)
{
	Super::Tick(DeltaSeconds);
//	FVector2D panelZeroDimensions = PanelZero->GetSprite()->GetSourceSize();
//	// UE_LOG(LogTemp, Warning, FString::Printf(TEXT("Dims: <%f, %f>"), panelZeroDimensions[0], panelZeroDimensions[1]));
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Dims: <%f, %f>"), panelZeroDimensions[0], panelZeroDimensions[1]));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Width: %f"), Width));
	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}