
#include "Components/ConstantSpeedComponent.h"
#include "DataAssets/ScoreSpeedProfile.h"

UConstantSpeedComponent::UConstantSpeedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

double
UConstantSpeedComponent::GetSpeed()
{
	if (bIsSpeedDisabled)
		return 0;

	return (UseProfile ? Profile->BaseSpeed : Speed) * (UseProfile ? Profile->ScaleMultiplier : ScaleMultiplier);
}

