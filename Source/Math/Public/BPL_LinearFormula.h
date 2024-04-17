#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPL_LinearFormula.generated.h"

struct FLinearData;

/**
 * 
 */
UCLASS()
class MATH_API UBPL_LinearFormula : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearData CreateFormula(float A, float B) noexcept;

	UFUNCTION(BlueprintCallable)
	static void SetSlope(UPARAM(ref) FLinearData& Data, float Slope) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetX(const FLinearData& Data, float Y) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetY(const FLinearData& Data, float X) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetRoot(const FLinearData& Data, FVector2D& Root) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetYIntercept(const FLinearData& Data, FVector2D& YIntercept) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString ToString(const FLinearData& Data) noexcept;

private:
	UFUNCTION()
	static void WithAB(FLinearData& Data, float A, float B) noexcept;
};
