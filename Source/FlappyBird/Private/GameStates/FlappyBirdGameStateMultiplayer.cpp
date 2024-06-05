// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/FlappyBirdGameStateMultiplayer.h"

AFlappyBirdGameStateMultiplayer::AFlappyBirdGameStateMultiplayer()
{
	OnLeadPlayerDiedDelegate.BindDynamic(this, &ThisClass::OnLeadPlayerDied);
	OnLeadPlayerDiedEvent.Add(OnLeadPlayerDiedDelegate);
}

AFlappyBirdGameStateMultiplayer::~AFlappyBirdGameStateMultiplayer()
{
	OnLeadPlayerDiedEvent.Remove(OnLeadPlayerDiedDelegate);
	OnLeadPlayerDiedDelegate.Unbind();
}

void
AFlappyBirdGameStateMultiplayer::NotifyPlayerJoined(
	APlayerController* PlayerController
)
{
	Super::NotifyPlayerJoined(PlayerController);

	if (CurrentLeadingPlayer == nullptr)
		CurrentLeadingPlayer = PlayerController;
}

void
AFlappyBirdGameStateMultiplayer::NotifyPlayerLeft(
	AController* Controller
)
{
	Super::NotifyPlayerLeft(Controller);

	StartedPlayers.Remove(Controller);
	DeadPlayers.Remove(Controller);
	CurrentLeadingPlayer = GetNextLeadingPlayer();
}


AController*
AFlappyBirdGameStateMultiplayer::GetLeadingPlayer()
{
	return CurrentLeadingPlayer;
}

bool
AFlappyBirdGameStateMultiplayer::IsLeadingPlayer(
	const AController* Player
)
{
	return Player == GetLeadingPlayer();
}

void
AFlappyBirdGameStateMultiplayer::OnPlayerStarted(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerStarted(PlayerCharacter);
	
	StartedPlayers.Add(PlayerCharacter->Controller);
	OnPlayerStartedEvent.Broadcast(PlayerCharacter);

	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerStartedEvent.Broadcast(PlayerCharacter);
	
	if (StartedPlayers.Num() == PlayerArray.Num())
		OnAllPlayersStartedEvent.Broadcast();
}

void
AFlappyBirdGameStateMultiplayer::OnPlayerDied(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerDied(PlayerCharacter);

	DeadPlayers.Add(PlayerCharacter->Controller);
	OnPlayerDiedEvent.Broadcast(PlayerCharacter);

	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerDiedEvent.Broadcast(PlayerCharacter);

	if (DeadPlayers.Num() == PlayerArray.Num())
		OnAllPlayersDiedEvent.Broadcast();
}

void
AFlappyBirdGameStateMultiplayer::OnPlayerPassedObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerPassedObstacle(PlayerCharacter);

	OnPlayerPassedObstacleEvent.Broadcast(PlayerCharacter);

	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerPassedObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateMultiplayer::OnPlayerHitObstacle(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitObstacle(PlayerCharacter);

	OnPlayerHitObstacleEvent.Broadcast(PlayerCharacter);
	
	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerHitObstacleEvent.Broadcast(PlayerCharacter);
}

void
AFlappyBirdGameStateMultiplayer::OnPlayerHitGround(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerHitGround(PlayerCharacter);

	OnPlayerHitGroundEvent.Broadcast(PlayerCharacter);

	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerHitGroundEvent.Broadcast(PlayerCharacter);

}

void
AFlappyBirdGameStateMultiplayer::OnPlayerFlapped(
	ABirdCharacter* PlayerCharacter
)
{
	Super::OnPlayerFlapped(PlayerCharacter);

	OnPlayerFlappedEvent.Broadcast(PlayerCharacter);

	if (IsLeadingPlayer(PlayerCharacter->Controller))
		OnLeadPlayerFlappedEvent.Broadcast(PlayerCharacter);
}

AController*
AFlappyBirdGameStateMultiplayer::GetNextLeadingPlayer()
{
	const auto OldLead = CurrentLeadingPlayer;
	auto NextLead = OldLead;

	for (const auto PlayerState : PlayerArray)
	{
		const auto& Controller = PlayerState->GetPlayerController();
		if (Controller == nullptr)
			continue;

		if (NextLead != Controller &&
			!DeadPlayers.Contains(Controller) &&
			NextLead != OldLead)
		{
			NextLead = Controller;
			return NextLead;
		}
	}
	
	return NextLead;
}

void
AFlappyBirdGameStateMultiplayer::OnLeadPlayerDied(
	ABirdCharacter* 
)
{
	CurrentLeadingPlayer = GetNextLeadingPlayer();
}
