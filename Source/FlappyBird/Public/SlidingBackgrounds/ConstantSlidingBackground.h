// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlidingBackground.h"
#include "CoreMinimal.h"
#include "ConstantSlidingBackground.generated.h"

class USpeedComponent;

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AConstantSlidingBackground : public ASlidingBackground
{
	GENERATED_BODY()

	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USpeedComponent> SpeedComponent;
	
public:
	AConstantSlidingBackground();

	virtual double CalcNextProgression(float DeltaTime) override;
};
