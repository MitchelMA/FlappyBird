// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdGameModeMultiplayer.generated.h"

UCLASS(BlueprintType)
class FLAPPYBIRD_API AFlappyBirdGameModeMultiplayer : public AFlappyBirdGameMode
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<AActor*, bool> UsedSpawnPoints;
	UPROPERTY()
	TMap<AController*, AActor*> PlayerUsedSpawns;

public:
	AFlappyBirdGameModeMultiplayer();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
