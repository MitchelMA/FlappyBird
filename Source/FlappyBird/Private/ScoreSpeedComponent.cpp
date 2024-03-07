#include "ScoreSpeedComponent.h"

#include "ScoreCounter.h"
#include "Kismet/GameplayStatics.h"

AScoreCounter*
UScoreSpeedComponent::GetScoreCounter()
{
	if (ScoreCounter != nullptr)
		return ScoreCounter;

	ScoreCounter = Cast<AScoreCounter>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AScoreCounter::StaticClass()));
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