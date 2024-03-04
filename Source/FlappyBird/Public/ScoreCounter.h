// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreCounter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScoreIncreasedDelegate, int64, TotalAmount, int64, Diff);

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AScoreCounter final : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	int64 Score = 0;
	
public:	
	// Sets default values for this actor's properties
	AScoreCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void IncreaseScore(int64 Amount = 1);
	FORCEINLINE int64 GetScore() const { return Score; }

	UPROPERTY(Category=Events, BlueprintAssignable)
	FScoreIncreasedDelegate OnScoreIncreased;
};
