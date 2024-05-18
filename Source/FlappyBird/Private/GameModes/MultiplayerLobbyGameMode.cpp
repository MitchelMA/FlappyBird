#include "GameModes/MultiplayerLobbyGameMode.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/BP_EmptyCharacter"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}
