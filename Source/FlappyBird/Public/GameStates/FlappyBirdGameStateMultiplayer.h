// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlappyBirdGameState.h"
#include "FlappyBirdGameStateMultiplayer.generated.h"

UCLASS(BlueprintType)
class FLAPPYBIRD_API AFlappyBirdGameStateMultiplayer : public AFlappyBirdGameState
{
	GENERATED_BODY()

	UPROPERTY()
	AController* CurrentLeadingPlayer = nullptr;

	UPROPERTY()
	TArray<AController*> StartedPlayers;
	
	UPROPERTY()
	TArray<AController*> DeadPlayers;

public:
	AFlappyBirdGameStateMultiplayer();
	virtual ~AFlappyBirdGameStateMultiplayer() override;

	virtual void NotifyPlayerJoined(APlayerController* PlayerController) override;
	virtual void NotifyPlayerLeft(AController* Controller) override;

	virtual AController* GetLeadingPlayer() override;
	virtual bool IsLeadingPlayer(const AController* Player) override;

	virtual void OnPlayerStarted(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerDied(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerPassedObstacle(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerHitObstacle(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerHitGround(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerFlapped(ABirdCharacter* PlayerCharacter) override;

protected:
	AController* GetNextLeadingPlayer();

	FOnLeadPlayerDied::FDelegate OnLeadPlayerDiedDelegate;
	UFUNCTION()
	void OnLeadPlayerDied(ABirdCharacter* PlayerCharacter);
};
