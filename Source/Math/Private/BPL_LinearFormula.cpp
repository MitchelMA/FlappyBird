#include "BPL_LinearFormula.h"
#include "LinearData.h"

FLinearData
UBPL_LinearFormula::CreateFormula(
	const float Slope,
	const float Offset
) noexcept
{
	FLinearData LinearData = {};
	WithAB(LinearData, Slope, Offset);
	return LinearData;
}



float
UBPL_LinearFormula::GetSlope(
	const FLinearData& Formula
) noexcept
{
	if (FMath::IsNearlyZero(Formula.ComponentQ))
		return INFINITY;

	return - Formula.ComponentP / Formula.ComponentQ;
}

void
UBPL_LinearFormula::SetSlope(
	FLinearData& Formula,
	const float Slope
) noexcept
{
	if (!FMath::IsFinite(Slope))
	{
		Formula.ComponentP = 1;
		Formula.ComponentQ = 0;
		return;
	}

	Formula.ComponentP = -Slope;
	Formula.ComponentQ = 1;
}

float
UBPL_LinearFormula::GetX(
	const FLinearData& Formula,
	const float Y
) noexcept
{
	if (!FMath::IsNearlyZero(Formula.ComponentP))
		return (Formula.ComponentR - Formula.ComponentQ * Y) / Formula.ComponentP;
	return INFINITY;
}

float
UBPL_LinearFormula::GetY(
	const FLinearData& Formula,
	const float X
) noexcept
{
	if (!FMath::IsNearlyZero(Formula.ComponentQ))
		return (Formula.ComponentR - Formula.ComponentP * X) / Formula.ComponentQ;
	return INFINITY;
}

bool
UBPL_LinearFormula::GetRoot(
	const FLinearData& Formula,
	FVector2D& Root
) noexcept
{
	if (FMath::IsNearlyZero(Formula.ComponentP))
	{
		Root[0] = GetX(Formula, 0);
		Root[1] = 0;
		return true;
	}

	if (FMath::IsNearlyZero(Formula.ComponentR))
	{
		Root[0] = INFINITY;
		Root[1] = 0;
		return true;
	}

	return false;
}

bool
UBPL_LinearFormula::GetYIntercept(
	const FLinearData& Formula,
	FVector2D& YIntercept
) noexcept
{
	if (FMath::IsNearlyZero(Formula.ComponentQ))
	{
		if (FMath::IsNearlyZero(Formula.ComponentR))
		{
			YIntercept[0] = 0;
			YIntercept[1] = INFINITY;
			return true;
		}

		return false;
	}

	YIntercept[0] = 0;
	YIntercept[1] = GetY(Formula, 0);
	return true;
}

FMatrix
UBPL_LinearFormula::ReducedEchelon(
	const FLinearData& FormulaA,
	const FLinearData& FormulaB
) noexcept
{
	FMatrix Matrix = FMatrix(
		{FormulaA.ComponentP, FormulaA.ComponentQ, FormulaA.ComponentR },
		{FormulaB.ComponentP, FormulaB.ComponentQ, FormulaB.ComponentR },
		{0, 0, 0 },
		{0, 0, 0 }
	);

	if (FMath::IsNearlyZero(Matrix.M[0][0]))
		Swap(Matrix.M[0], Matrix.M[1]);

	Matrix.M[0][1] /= Matrix.M[0][0];
	Matrix.M[0][2] /= Matrix.M[0][0];
	Matrix.M[0][0] /= Matrix.M[0][0];

	Matrix.M[1][1] -= Matrix.M[1][0] * Matrix.M[0][1];
	Matrix.M[1][2] -= Matrix.M[1][0] * Matrix.M[0][2];
	Matrix.M[1][0] -= Matrix.M[1][0] * Matrix.M[0][0];

	Matrix.M[1][0] /= Matrix.M[1][1];
	Matrix.M[1][2] /= Matrix.M[1][1];
	Matrix.M[1][1] /= Matrix.M[1][1];

	Matrix.M[0][0] -= Matrix.M[0][1] * Matrix.M[1][0];
	Matrix.M[0][2] -= Matrix.M[0][1] * Matrix.M[1][2];
	Matrix.M[0][1] -= Matrix.M[0][1] * Matrix.M[1][1];

	return Matrix;
}

ELinearIntersectionType
UBPL_LinearFormula::DoesIntersect(
	const FLinearData& FormulaA,
	const FLinearData& FormulaB,
	const float Tolerance
) noexcept
{
	const auto ASlope = GetSlope(FormulaA);
	const auto BSlope = GetSlope(FormulaB);
	auto SlopeDiff = abs(ASlope - BSlope);

	
	if (!FMath::IsFinite(ASlope) && !FMath::IsFinite(BSlope))
		SlopeDiff = 0;

	if (SlopeDiff > Tolerance)
		return ELinearIntersectionType::Once;

	if (abs(FormulaA.ComponentR / FormulaA.ComponentQ - FormulaB.ComponentR / FormulaB.ComponentQ) < Tolerance)
		return ELinearIntersectionType::Continuous;

	return ELinearIntersectionType::None;
		
}

FVector2D
UBPL_LinearFormula::GetPointOfIntersection(
	const FLinearData& FormulaA,
	const FLinearData& FormulaB,
	TEnumAsByte<ELinearIntersectionType>& IntersectionType
) noexcept
{
	IntersectionType = DoesIntersect(FormulaA, FormulaB);
	if (IntersectionType == ELinearIntersectionType::None)
		return {0.f, 0.f};

	if (IntersectionType == ELinearIntersectionType::Continuous)
		return {INFINITY, INFINITY};

	const auto IntersectionMatrix = ReducedEchelon(FormulaA, FormulaB);
	return {IntersectionMatrix.M[0][2], IntersectionMatrix.M[1][2]};
}

FLinearData
UBPL_LinearFormula::Normalised(
	const FLinearData& Formula
) noexcept
{
	FLinearData Copy = Formula;
	Normalise(Copy);
	return Copy;
}

void
UBPL_LinearFormula::Normalise(
	FLinearData& Formula
) noexcept
{
	const auto FirstNonEmpty = FirstNonEmptyMember(Formula);
	if (FirstNonEmpty == -1)
		return;
	
	const auto Dividend = 1.f / (&(Formula.ComponentP))[FirstNonEmpty];
	Formula.ComponentP *= Dividend;
	Formula.ComponentQ *= Dividend;
	Formula.ComponentR *= Dividend;
}

bool
UBPL_LinearFormula::IsNormalised(
	const FLinearData& Formula
) noexcept
{
	const auto FirstNOnEmpty = FirstNonEmptyMember(Formula);
	if (FirstNOnEmpty == -1)
		return false;
	return FMath::IsNearlyEqual((&(Formula.ComponentP))[FirstNOnEmpty], 1);
}

bool
UBPL_LinearFormula::Equals(
	const FLinearData& FormulaA,
	const FLinearData& FormulaB
) noexcept
{
	const auto NormalisedA = Normalised(FormulaA);
	const auto NormalisedB = Normalised(FormulaB);

	return (
		NormalisedA.ComponentP == NormalisedB.ComponentP &&
		NormalisedA.ComponentQ == NormalisedB.ComponentQ &&
		NormalisedA.ComponentR == NormalisedB.ComponentR
	);
}

FString
UBPL_LinearFormula::ToString(
	const FLinearData& Formula
) noexcept
{
	return FString::Printf(TEXT("%fx + %fy = %f"),
		Formula.ComponentP, Formula.ComponentQ, Formula.ComponentR);
}

void
UBPL_LinearFormula::WithAB(
	FLinearData& Formula,
	const float A,
	const float B
) noexcept
{
	SetSlope(Formula, A);
	Formula.ComponentR = B;
}


int32
UBPL_LinearFormula::FirstNonEmptyMember(
	const FLinearData& Formula
) noexcept
{
	for (int32 i = 0; i < 3; i++)
		if (abs((&(Formula.ComponentP))[i]) > 0.0001f)
			return i;
	return -1;
}