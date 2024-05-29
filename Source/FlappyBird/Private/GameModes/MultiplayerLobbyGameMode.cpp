#include "GameModes/MultiplayerLobbyGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/MultiplayerLobbyPlayerController.h"

AMultiplayerLobbyGameMode::AMultiplayerLobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/BP_EmptyCharacter"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;

	PlayerControllerClass = AMultiplayerLobbyPlayerController::StaticClass();

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
	if (const auto UsedSpawnPoint = PlayerUsedSpawns.Find(Exiting))
	{
		if (const auto IsUsed = UsedSpawnPoints.Find(*UsedSpawnPoint))
			*IsUsed = false;
	}
	PlayerUsedSpawns.Remove(Exiting);
	OnPlayerLogoutEvent.Broadcast(Exiting);
}

AActor*
AMultiplayerLobbyGameMode::ChoosePlayerStart_Implementation(
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

