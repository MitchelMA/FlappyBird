// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpeedComponent.h"
#include "ScoreSpeedComponent.generated.h"

class AScoreCounter;

/**
 * 
 */
UCLASS(ClassGroup=(Speed), meta=(BlueprintSpawnableComponent=true))
class FLAPPYBIRD_API UScoreSpeedComponent : public USpeedComponent
{
	GENERATED_BODY()

	TObjectPtr<AScoreCounter> ScoreCounter = nullptr;

	UPROPERTY(Category=SpeedSettings, EditAnywhere)
	float BaseSpeed = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere)
	float ScoreMultiplier = 1.f;
	
	AScoreCounter* GetScoreCounter();
	
public:

	virtual double GetSpeed() override;
};
