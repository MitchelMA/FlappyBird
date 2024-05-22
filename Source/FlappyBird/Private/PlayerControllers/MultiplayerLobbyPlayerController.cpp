#include "PlayerControllers/MultiplayerLobbyPlayerController.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(LogMultiplayerLobbyPlayerController)

AMultiplayerLobbyPlayerController::AMultiplayerLobbyPlayerController()
{
	const ConstructorHelpers::FClassFinder<UUserWidget> LobbyMenuWidgetClassHost(TEXT("/Game/FlappyBird/Blueprints/Widgets/WBP_MultiplayerLobbyMenu_Host"));
	const ConstructorHelpers::FClassFinder<UUserWidget> LobbyMenuWidgetClassClient(TEXT("/Game/FlappyBird/Blueprints/Widgets/WBP_MultiplayerLobbyMenu_Client"));
	LobbyMenuWidgetHost = LobbyMenuWidgetClassHost.Class;
	LobbyMenuWidgetClient = LobbyMenuWidgetClassClient.Class;
}

void
AMultiplayerLobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(LobbyMenuWidgetHost))
	{
		UE_LOG(LogMultiplayerLobbyPlayerController, Error,
			TEXT("Unable to find User Widget for Lobby Main Menu"));
		return;
	}

	ApplyWidget();
}

void
AMultiplayerLobbyPlayerController::ApplyWidget_Implementation()
{
	const auto& TargetWidget = HasAuthority() ? LobbyMenuWidgetHost : LobbyMenuWidgetClient;

	const auto CreatedWidget = CreateWidget(
		GetWorld()->GetFirstPlayerController(),
		TargetWidget,
		TEXT("Lobby Menu")
	);
	CreatedWidget->AddToViewport();
	SetShowMouseCursor(true);
}
