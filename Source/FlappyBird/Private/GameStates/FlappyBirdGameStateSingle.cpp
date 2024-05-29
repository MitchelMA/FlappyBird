#include "GameStates/FlappyBirdGameStateSingle.h"

AFlappyBirdGameStateSingle::AFlappyBirdGameStateSingle()
{
}

AController*
AFlappyBirdGameStateSingle::GetLeadingPlayer()
{
	return PlayerArray[0]->GetPlayerController();
}

bool AFlappyBirdGameStateSingle::IsLeadPlayer(const AController* Player)
{
	 return Player == GetLeadingPlayer();
}

void AFlappyBirdGameStateSingle::OnPlayerStarted(ABirdCharacter* PlayerCharacter)
{
	Super::OnPlayerStarted(PlayerCharacter);
	OnPlayerStartedEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerStartedEvent.Broadcast(PlayerCharacter);
	OnAllPlayersStartedEvent.Broadcast();
}

void
AFlappyBirdGameStateSingle::OnPlayerDied(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerDied(PlayerCharacter);
	OnPlayerDiedEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerDiedEvent.Broadcast(PlayerCharacter);
	OnAllPlayersDiedEvent.Broadcast();
}

void
AFlappyBirdGameStateSingle::OnPlayerPassedObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerPassedObstacle(PlayerCharacter);
	OnPlayerPassedObstacleEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerPassedObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerHitObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitObstacle(PlayerCharacter);
	OnPlayerHitObstacleEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerHitObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerHitGround(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitGround(PlayerCharacter);
	OnPlayerHitGroundEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerHitGroundEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerFlapped(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerFlapped(PlayerCharacter);
	OnPlayerFlappedEvent.Broadcast(PlayerCharacter);
	OnLeadPlayerFlappedEvent.Broadcast(PlayerCharacter);
}
