#include "ScoreSpeedComponent.h"

#include "ScoreCounter.h"
#include "ScoreSpeedProfile.h"
#include "TemplatedBlueprintMethods.h"

DEFINE_LOG_CATEGORY(LogScoreSpeedComponent);

AScoreCounter*
UScoreSpeedComponent::GetScoreCounter()
{
	if (IsValid(ScoreCounter))
		return ScoreCounter;

	ScoreCounter = Templated::GetActorOfClass<AScoreCounter>(GetWorld());
	if (!IsValid(ScoreCounter))
		UE_LOG(LogScoreSpeedComponent, Warning, TEXT("Unable to find a ScoreCounter in current level"));
	
	return ScoreCounter;
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
