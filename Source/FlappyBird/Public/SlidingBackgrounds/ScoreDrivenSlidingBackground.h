#pragma once

#include "SlidingBackground.h"
#include "CoreMinimal.h"
#include "ScoreDrivenSlidingBackground.generated.h"

class USpeedComponent;

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AScoreDrivenSlidingBackground : public ASlidingBackground
{
	GENERATED_BODY()

	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USpeedComponent> SpeedComponent = nullptr;
	
public:
	AScoreDrivenSlidingBackground();

	virtual double CalcNextProgression(float DeltaTime) override;
};
