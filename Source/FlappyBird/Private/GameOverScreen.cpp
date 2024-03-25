// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverScreen.h"

#include "ResetInstigator.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameOverScreen::AGameOverScreen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(DefaultSceneRoot);
	// Draw the widget to the screen, not the world
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	// Sets the correct game-over Widget Blueprint class to use
	Widget->SetWidgetClass(ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("/Game/FlappyBird/Blueprints/UI/WBP_GameOver")).Class);
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
	PlayerController->SetPause(false);
}

void
AGameOverScreen::Open()
const noexcept
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetPause(true);
}

void
AGameOverScreen::OnRestartClicked()
const noexcept
{
	Close();
	const auto ResetInstigator = Cast<AResetInstigator>(UGameplayStatics::GetActorOfClass(GetWorld(), AResetInstigator::StaticClass()));
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

