
#include "SlidingBackgrounds/ConstantSlidingBackground.h"
#include "Components/SpeedComponent.h"
#include "Components/ConstantSpeedComponent.h"


AConstantSlidingBackground::AConstantSlidingBackground()
	: Super()
{
	SpeedComponent = Cast<USpeedComponent>(CreateDefaultSubobject<UConstantSpeedComponent>(TEXT("SpeedComponent")));
	SpeedComponent->SetIsReplicated(true);
}

double
AConstantSlidingBackground::CalcNextProgression(
	const float DeltaTime
)
{
	const auto NextXOffset = PanelOffset->GetRelativeLocation()[0] + DeltaTime * HorizontalDirectionMultiplier * SpeedComponent->GetSpeed();
	Progression = fabs(NextXOffset) / GetPanelSize()[0];
	Progression = fmod(Progression, 1);
	return Progression;
}


