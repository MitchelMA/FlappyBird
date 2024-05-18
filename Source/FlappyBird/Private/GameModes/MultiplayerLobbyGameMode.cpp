#include "GameModes/MultiplayerLobbyGameMode.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	// DefaultPawnClass = nullptr;
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/BP_BirdCharacter"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}

void
AMultiplayerLobbyGameMode::PostLogin(
	APlayerController* NewPlayer
)
{
	Super::PostLogin(NewPlayer);

	OnPlayerJoinedEvent.Broadcast(NewPlayer);
}
