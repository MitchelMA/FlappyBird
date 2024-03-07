#pragma once

#include "CoreMinimal.h"
#include "SpeedComponent.h"
#include "ScoreSpeedComponent.generated.h"

class AScoreCounter;

/**
 * 
 */
UCLASS(ClassGroup=(Speed), meta=(BlueprintSpawnableComponent=true))
class FLAPPYBIRD_API UScoreSpeedComponent : public USpeedComponent
{
	GENERATED_BODY()

	TObjectPtr<AScoreCounter> ScoreCounter = nullptr;

	UPROPERTY(Category=SpeedSettings, EditAnywhere)
	float BaseSpeed = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere)
	float ScoreMultiplier = 1.f;

	UPROPERTY(Category=SpeedSettings, EditAnywhere)
	float ScaleMultiplier = 1.f;
	
	AScoreCounter* GetScoreCounter();
	
public:

	virtual double GetSpeed() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetBaseSpeed() const noexcept { return BaseSpeed; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBaseSpeed(const float NewBaseSpeed) noexcept { BaseSpeed = NewBaseSpeed; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetScoreMultiplier() const noexcept { return ScoreMultiplier; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetScoreMultiplier(const float NewScoreMultiplier) { ScoreMultiplier = NewScoreMultiplier; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetScaleMultiplier() const noexcept { return ScaleMultiplier; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetScaleMultiplier(const float NewScaleMultiplier) { ScaleMultiplier = NewScaleMultiplier; }
};
