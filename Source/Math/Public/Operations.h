#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Operations.generated.h"

UCLASS()
class MATH_API UOperations : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Operator")
	static FORCEINLINE float Diff(const float A, const float B)
	{
		return FMath::Abs(A - B);
	}
};
