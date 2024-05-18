#include "GameStates/FlappyBirdGameStateSingle.h"

AFlappyBirdGameStateSingle::AFlappyBirdGameStateSingle()
{
}

AController*
AFlappyBirdGameStateSingle::GetLeadingPlayer()
{
	return PlayerArray[0]->GetPlayerController();
}

void AFlappyBirdGameStateSingle::OnPlayerStarted(ABirdCharacter* PlayerCharacter)
{
	Super::OnPlayerStarted(PlayerCharacter);
	OnPlayerStartedEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerDied(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerDied(PlayerCharacter);
	OnPlayerDiedEvent.Broadcast(PlayerCharacter);
	OnAllPlayersDiedEvent.Broadcast();
}

void
AFlappyBirdGameStateSingle::OnPlayerPassedObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerPassedObstacle(PlayerCharacter);
	OnPlayerPassedObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerHitObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitObstacle(PlayerCharacter);
	OnPlayerHitObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerHitGround(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitGround(PlayerCharacter);
	OnPlayerHitGroundEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateSingle::OnPlayerFlapped(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerFlapped(PlayerCharacter);
	OnPlayerFlappedEvent.Broadcast(PlayerCharacter);
}
