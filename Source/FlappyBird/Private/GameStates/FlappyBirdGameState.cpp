#include "GameStates/FlappyBirdGameState.h"

#include "PlayerStates/FlappyBirdPlayerState.h"


AFlappyBirdGameState::AFlappyBirdGameState()
{
	OnBirdStartedDelegate.BindDynamic(this, &ThisClass::OnPlayerStarted);
	OnBirdDiedDelegate.BindDynamic(this, &ThisClass::OnPlayerDied);
	OnBirdPassedObstacleDelegate.BindDynamic(this, &ThisClass::OnPlayerPassedObstacle);
	OnBirdHitObstacleDelegate.BindDynamic(this, &ThisClass::OnPlayerHitObstacle);
	OnBirdHitGroundDelegate.BindDynamic(this, &ThisClass::OnPlayerHitGround);
	OnBirdFlappedDelegate.BindDynamic(this, &ThisClass::OnPlayerFlapped);
}

void
AFlappyBirdGameState::EndPlay(
	const EEndPlayReason::Type EndPlayReason
)
{
	Super::EndPlay(EndPlayReason);

	OnBirdStartedDelegate.Unbind();
	OnBirdDiedDelegate.Unbind();
	OnBirdPassedObstacleDelegate.Unbind();
	OnBirdHitObstacleDelegate.Unbind();
	OnBirdHitGroundDelegate.Unbind();
	OnBirdFlappedDelegate.Unbind();
}

void
AFlappyBirdGameState::NotifyPlayerJoined(
	APlayerController* PlayerController
)
{
	const auto PlayerState = PlayerController->GetPlayerState<AFlappyBirdPlayerState>();
	if (!PlayerState)
		return;

	PlayerState->OnBirdStartedEvent.Add(OnBirdStartedDelegate);
	PlayerState->OnBirdDiedEvent.Add(OnBirdDiedDelegate);
	PlayerState->OnBirdPassedObstacleEvent.Add(OnBirdPassedObstacleDelegate);
	PlayerState->OnBirdHitObstacleEvent.Add(OnBirdHitObstacleDelegate);
	PlayerState->OnBirdHitGroundEvent.Add(OnBirdHitGroundDelegate);
	PlayerState->OnBirdFlappedEvent.Add(OnBirdFlappedDelegate);
}

void
AFlappyBirdGameState::NotifyPlayerLeft(
	AController* Controller
)
{
	const auto PlayerState = Controller->GetPlayerState<AFlappyBirdPlayerState>();
	if (!PlayerState)
		return;

	PlayerState->OnBirdStartedEvent.Remove(OnBirdStartedDelegate);
	PlayerState->OnBirdDiedEvent.Remove(OnBirdDiedDelegate);
	PlayerState->OnBirdPassedObstacleEvent.Remove(OnBirdPassedObstacleDelegate);
	PlayerState->OnBirdHitObstacleEvent.Remove(OnBirdHitObstacleDelegate);
	PlayerState->OnBirdHitGroundEvent.Remove(OnBirdHitGroundDelegate);
	PlayerState->OnBirdFlappedEvent.Remove(OnBirdFlappedDelegate);
}
