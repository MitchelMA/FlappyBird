#include "ScoreSpeedComponent.h"

#include "ScoreCounter.h"
#include "ScoreSpeedProfile.h"
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
	return (GetBaseSpeed() + CurrentScore * GetScoreAddition()) * GetScaleMultiplier();
}

float
UScoreSpeedComponent::GetBaseSpeed()
const noexcept
{
	return UseProfile ?
		Profile->BaseSpeed :
		BaseSpeed;
}

void
UScoreSpeedComponent::SetBaseSpeed(
	const float NewBaseSpeed
) noexcept
{
	UseProfile ?
		Profile->BaseSpeed = NewBaseSpeed :
		BaseSpeed = NewBaseSpeed;
}

float
UScoreSpeedComponent::GetScoreAddition()
const noexcept
{
	return UseProfile ?
		Profile->ScoreAddition :
		ScoreAddition;
}

void
UScoreSpeedComponent::SetScoreAddition(
	const float NewScoreAddition
) noexcept
{
	UseProfile ?
		Profile->ScoreAddition = NewScoreAddition :
		ScoreAddition = NewScoreAddition;
}

float
UScoreSpeedComponent::GetScaleMultiplier()
const noexcept
{
	return UseProfile ?
		Profile->ScaleMultiplier :
		ScaleMultiplier;
}

void
UScoreSpeedComponent::SetScaleMultiplier(
	const float NewScaleMultiplier
) noexcept
{
	UseProfile ?
		Profile->ScaleMultiplier = NewScaleMultiplier :
		ScaleMultiplier = NewScaleMultiplier;
}
