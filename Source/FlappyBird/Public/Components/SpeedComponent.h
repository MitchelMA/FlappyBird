// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeedComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSpeedComponent, Log, All);

UCLASS(Abstract, ClassGroup=(Speed))
class FLAPPYBIRD_API USpeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpeedComponent() = default;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category=SpeedSettings,
		BlueprintGetter=GetIsSpeedDisabled)
	bool bIsSpeedDisabled = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual double GetSpeed();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetIsSpeedDisabled() const noexcept { return bIsSpeedDisabled; }
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void SetIsSpeedDisabled(const bool IsDisabled);
};
