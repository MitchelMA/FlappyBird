#include "GameModes/FlappyBirdGameModeSingle.h"

#include "GameStates/FlappyBirdGameStateSingle.h"

AFlappyBirdGameModeSingle::AFlappyBirdGameModeSingle()
	: AFlappyBirdGameMode()
{
	GameStateClass = AFlappyBirdGameStateSingle::StaticClass();
	PlayerStateClass = AFlappyBirdPlayerState::StaticClass();
}

void
AFlappyBirdGameModeSingle::PostLogin(
	APlayerController* NewPlayer
)
{
	Super::PostLogin(NewPlayer);
	
	Cast<AFlappyBirdGameState>(GameState)->NotifyPlayerJoined(NewPlayer);
}

void AFlappyBirdGameModeSingle::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	Cast<AFlappyBirdGameState>(GameState)->NotifyPlayerLeft(Exiting);
}
