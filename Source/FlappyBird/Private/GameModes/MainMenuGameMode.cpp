
#include "GameModes/MainMenuGameMode.h"

#include "Multiplayer/MultiplayerSubsystem.h"
#include "PlayerControllers/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
}

void AMainMenuGameMode::BeginPlay()
{
	const auto MultiplayerSubsystem = GetGameInstance()->GetSubsystem<UMultiplayerSubsystem>();
	MultiplayerSubsystem->DestroyGameSession();
}
