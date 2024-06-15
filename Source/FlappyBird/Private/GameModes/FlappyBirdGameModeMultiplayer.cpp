#include "GameModes/FlappyBirdGameModeMultiplayer.h"
#include "GameStates/FlappyBirdGameState.h"
#include "GameStates/FlappyBirdGameStateMultiplayer.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AFlappyBirdGameModeMultiplayer::AFlappyBirdGameModeMultiplayer()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/Characters/BP_BirdCharacterMulti"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;
	
	GameStateClass = AFlappyBirdGameStateMultiplayer::StaticClass();
	PlayerStateClass = AFlappyBirdPlayerState::StaticClass();

	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		APlayerStart::StaticClass(),
		PlayerStarts
	);

	for (const auto PlayerStart : PlayerStarts)
		UsedSpawnPoints.Add(PlayerStart, false);
}

void
AFlappyBirdGameModeMultiplayer::PostLogin(
	APlayerController* NewPlayer
)
{
	Super::PostLogin(NewPlayer);

	Cast<AFlappyBirdGameState>(GameState)->NotifyPlayerJoined(NewPlayer);
}

void
AFlappyBirdGameModeMultiplayer::Logout(
	AController* Exiting
)
{
	Super::Logout(Exiting);

	Cast<AFlappyBirdGameState>(GameState)->NotifyPlayerLeft(Exiting);

	if (const auto UsedSpawnPoint = PlayerUsedSpawns.Find(Exiting))
	{
		if (const auto IsUsed = UsedSpawnPoints.Find(*UsedSpawnPoint))
			*IsUsed = false;
	}
}

AActor*
AFlappyBirdGameModeMultiplayer::ChoosePlayerStart_Implementation(
	AController* Player
)
{

	for (auto& [Start, AlreadyUsed] : UsedSpawnPoints)
	{
		if (AlreadyUsed)
			continue;

		AlreadyUsed = true;
		PlayerUsedSpawns.Add(Player, Start);
		return Start;
	}

	return UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
}
