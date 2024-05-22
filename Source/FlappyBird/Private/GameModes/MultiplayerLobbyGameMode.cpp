#include "GameModes/MultiplayerLobbyGameMode.h"
#include "PlayerControllers/MultiplayerLobbyPlayerController.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/BP_EmptyCharacter"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;

	PlayerControllerClass = AMultiplayerLobbyPlayerController::StaticClass();
}

void
AMultiplayerLobbyGameMode::PostLogin(
	APlayerController* NewPlayer
)
{
	Super::PostLogin(NewPlayer);

	OnPlayerLoginEvent.Broadcast(NewPlayer);
}

void
AMultiplayerLobbyGameMode::Logout(
	AController* Exiting
)
{
	Super::Logout(Exiting);

	OnPlayerLogoutEvent.Broadcast(Exiting);
}

