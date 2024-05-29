#include "SlidingBackgrounds/ScoreDrivenSlidingBackground.h"
#include "Components/SpeedComponent.h"
#include "Components/ScoreSpeedComponent.h"


AScoreDrivenSlidingBackground::AScoreDrivenSlidingBackground()
	: Super()
{
	SpeedComponent = Cast<USpeedComponent>(CreateDefaultSubobject<UScoreSpeedComponent>(TEXT("SpeedComponent")));
	SpeedComponent->SetIsReplicated(true);
}

double
AScoreDrivenSlidingBackground::CalcNextProgression(
	const float DeltaTime
)
{
	const auto NextXOffset = PanelOffset->GetRelativeLocation()[0] + DeltaTime * HorizontalDirectionMultiplier * SpeedComponent->GetSpeed();
	Progression = fabs(NextXOffset) / GetPanelSize()[0];
	Progression = fmod(Progression, 1);
	return Progression;
}

