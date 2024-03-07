// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSpeedComponent.h"

#include "ScoreCounter.h"
#include "Kismet/GameplayStatics.h"

AScoreCounter* UScoreSpeedComponent::GetScoreCounter()
{
	if (ScoreCounter != nullptr)
		return ScoreCounter;

	TArray<AActor*> Counters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScoreCounter::StaticClass(), Counters);
	ScoreCounter = Cast<AScoreCounter>(Counters[0]);
	
	return GetScoreCounter();
}

double
UScoreSpeedComponent::GetSpeed()
{
	if (bIsSpeedDisabled)
		return 0.;
	
	const auto CurrentScore = GetScoreCounter()->GetScore();
	return (BaseSpeed + CurrentScore * ScoreMultiplier) * ScaleMultiplier;
}
