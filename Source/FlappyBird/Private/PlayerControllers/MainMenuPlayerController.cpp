
#include "PlayerControllers/MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(LogMainMenuPlayerController)

AMainMenuPlayerController::AMainMenuPlayerController()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetClass(TEXT("/Game/FlappyBird/Blueprints/Widgets/WBP_MainMenu"));
	MainMenuWidget = MainMenuWidgetClass.Class;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(MainMenuWidget))
	{
		UE_LOG(LogMainMenuPlayerController, Error,
			TEXT("Unable to find User Widget of the Main Menu"));
		return;
	}

	const auto CreatedWidget = CreateWidget(
		GetWorld()->GetFirstPlayerController(),
		MainMenuWidget,
		TEXT("Main Menu")
	);
	CreatedWidget->AddToViewport();
	SetShowMouseCursor(true);
}
