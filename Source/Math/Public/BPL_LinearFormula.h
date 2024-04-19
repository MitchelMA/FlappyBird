#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LinearIntersectionType.h"
#include "BPL_LinearFormula.generated.h"

struct FLinearData;

UCLASS()
class MATH_API UBPL_LinearFormula : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FLinearData CreateFormula(float Slope, float Offset) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetSlope(const FLinearData& Formula) noexcept;
	UFUNCTION(BlueprintCallable)
	static void SetSlope(UPARAM(ref) FLinearData& Formula, float Slope) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetX(const FLinearData& Formula, float Y) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetY(const FLinearData& Formula, float X) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetRoot(const FLinearData& Formula, FVector2D& Root) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool GetYIntercept(const FLinearData& Formula, FVector2D& YIntercept) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FMatrix ReducedEchelon(const FLinearData& FormulaA, const FLinearData& FormulaB) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static ELinearIntersectionType DoesIntersect(const FLinearData& FormulaA, const FLinearData& FormulaB, float Tolerance = 1E-45) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector2D Intersect(const FLinearData& FormulaA, const FLinearData& FormulaB, TEnumAsByte<ELinearIntersectionType>& IntersectionType) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FLinearData Normalised(const FLinearData& Formula) noexcept;

	UFUNCTION(BlueprintCallable)
	static void Normalise(UPARAM(ref) FLinearData& Formula) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool IsNormalised(const FLinearData& Formula) noexcept;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool Equals(const FLinearData& FormulaA, const FLinearData& FormulaB) noexcept;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString ToString(const FLinearData& Formula) noexcept;

private:
	UFUNCTION()
	static void WithAB(FLinearData& Formula, float A, float B) noexcept;

	UFUNCTION()
	static int32 FirstNonEmptyMember(const FLinearData& Formula) noexcept;
};
