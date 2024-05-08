
#pragma once


#include "SpeedComponent.h"
#include "CoreMinimal.h"
#include "ConstantSpeedComponent.generated.h"

class UScoreSpeedProfile;

UCLASS(ClassGroup=(Speed), meta=(BlueprintSpawnableComponent=true))
class FLAPPYBIRD_API UConstantSpeedComponent : public USpeedComponent
{
	GENERATED_BODY()

	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float Speed = 1.f;
	
	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float ScaleMultiplier = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere, AdvancedDisplay,
		meta=(EditCondition="UseProfile", EditConditionHides=true))
	TObjectPtr<UScoreSpeedProfile> Profile;
	
	UPROPERTY(Category=SpeedSettings, EditAnywhere, AdvancedDisplay)
	bool UseProfile = false;

	public:
    	UConstantSpeedComponent();

	virtual double GetSpeed() override;
};
