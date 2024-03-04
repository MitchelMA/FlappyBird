// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCounter.h"

// Sets default values
AScoreCounter::AScoreCounter()
{
}

// Called when the game starts or when spawned
void
AScoreCounter::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
}

// Called every frame
void
AScoreCounter::Tick(
	 const float DeltaTime
)
{
	Super::Tick(DeltaTime);

}

void
AScoreCounter::IncreaseScore(
	const int64 Amount
)
{
	if (Amount == 0)
		return;
	
	Score += Amount;
	OnScoreIncreased.Broadcast(Score, Amount);
}
