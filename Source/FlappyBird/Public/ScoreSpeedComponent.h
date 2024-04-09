#pragma once

#include "CoreMinimal.h"
#include "SpeedComponent.h"
#include "ScoreSpeedComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogScoreSpeedComponent, Log, All);

class UScoreSpeedProfile;
class AScoreCounter;

UCLASS(ClassGroup=(Speed), meta=(BlueprintSpawnableComponent=true))
class FLAPPYBIRD_API UScoreSpeedComponent : public USpeedComponent
{
	GENERATED_BODY()

	TObjectPtr<AScoreCounter> ScoreCounter = nullptr;

	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float BaseSpeed = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float ScoreAddition = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float MaxSpeed = 0.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere,
		meta=(EditCondition="!UseProfile", EditConditionHides=true))
	float ScaleMultiplier = 1.f;
	
	UPROPERTY(Category=SpeedSettings, EditAnywhere, AdvancedDisplay)
	bool UseProfile;

	UPROPERTY(Category=SpeedSettings, EditAnywhere, AdvancedDisplay,
		meta=(EditCondition="UseProfile", EditConditionHides=true))
	TObjectPtr<UScoreSpeedProfile> Profile;
	
	AScoreCounter* GetScoreCounter();
	
public:

	virtual double GetSpeed() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseSpeed() const noexcept; 
	UFUNCTION(BlueprintCallable)
	void SetBaseSpeed(const float NewBaseSpeed) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetScoreAddition() const noexcept;
	UFUNCTION(BlueprintCallable)
	void SetScoreAddition(const float NewScoreAddition) noexcept; 

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxSpeed() const noexcept;
	UFUNCTION(BlueprintCallable)
	void SetMaxSpeed(const float NewMaxSpeed) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetScaleMultiplier() const noexcept;
	UFUNCTION(BlueprintCallable)
	void SetScaleMultiplier(const float NewScaleMultiplier) noexcept;
};
