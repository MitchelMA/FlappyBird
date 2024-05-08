// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverScreen.h"

#include "ResetInstigator.h"
#include "Helpers/TemplatedBlueprintMethods.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameOverScreen::AGameOverScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
}

// Called when the game starts or when spawned
void
AGameOverScreen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void
AGameOverScreen::Tick(
	const float DeltaTime
)
{
	Super::Tick(DeltaTime);

}

void
AGameOverScreen::Close()
const noexcept
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	PlayerController->bShowMouseCursor = false;
}

void
AGameOverScreen::Open()
const noexcept
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
	PlayerController->bShowMouseCursor = true;
}

void
AGameOverScreen::OnRestartClicked()
const noexcept
{
	Close();
	const auto ResetInstigator = Templated::GetActorOfClass<AResetInstigator>(GetWorld());
	ResetInstigator->ResetAll();
}

void
AGameOverScreen::OnQuitClicked()
const noexcept
{
	Close();
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}

