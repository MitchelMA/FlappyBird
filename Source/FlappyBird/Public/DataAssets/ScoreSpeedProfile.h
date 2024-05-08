#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScoreSpeedProfile.generated.h"

UCLASS()
class FLAPPYBIRD_API UScoreSpeedProfile : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	float BaseSpeed;

	UPROPERTY(EditAnywhere)
	float ScoreAddition;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	float ScaleMultiplier;

	UScoreSpeedProfile()
		: BaseSpeed(20.f), ScoreAddition(1.f), MaxSpeed(0.f), ScaleMultiplier(1.f)
	{}
};
