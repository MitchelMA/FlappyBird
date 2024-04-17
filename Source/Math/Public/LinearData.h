#pragma once

#include "CoreMinimal.h"
#include "LinearData.generated.h"


USTRUCT(Blueprintable)
struct MATH_API FLinearData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ComponentP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ComponentQ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ComponentR;

	FLinearData()
	{
		ComponentP = 0.f;
		ComponentQ = 0.f;
		ComponentR = 0.f;
	}
};
