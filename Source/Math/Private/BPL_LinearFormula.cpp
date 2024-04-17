#include "BPL_LinearFormula.h"

#include "LinearData.h"

FLinearData
UBPL_LinearFormula::CreateFormula(
	const float A,
	const float B
) noexcept
{
	FLinearData LinearData = {};
	WithAB(LinearData, A, B);
	return LinearData;
}

void
UBPL_LinearFormula::SetSlope(
	FLinearData& Data,
	const float Slope
) noexcept
{
	if (isinf(Slope))
	{
		Data.ComponentP = 1;
		Data.ComponentQ = 0;
		return;
	}

	Data.ComponentP = -Slope;
	Data.ComponentQ = 1;
}

float
UBPL_LinearFormula::GetX(
	const FLinearData& Data,
	const float Y
) noexcept
{
	if (Data.ComponentP != 0)
		return (Data.ComponentR - Data.ComponentQ * Y) / Data.ComponentP;
	return INFINITY;
}

float
UBPL_LinearFormula::GetY(
	const FLinearData& Data,
	const float X
) noexcept
{
	if (Data.ComponentQ != 0)
		return (Data.ComponentR - Data.ComponentP * X) / Data.ComponentQ;
	return INFINITY;
}

bool
UBPL_LinearFormula::GetRoot(
	const FLinearData& Data,
	FVector2D& Root
) noexcept
{
	if (abs(Data.ComponentP) >= 0.001f)
	{
		Root[0] = GetX(Data, 0);
		Root[1] = 0;
		return true;
	}

	if (abs(Data.ComponentR) <= 0.001f)
	{
		Root[0] = INFINITY;
		Root[1] = 0;
		return true;
	}

	return false;
}

bool
UBPL_LinearFormula::GetYIntercept(
	const FLinearData& Data,
	FVector2D& YIntercept
) noexcept
{
	if (abs(Data.ComponentQ) <= 0.001f)
	{
		if (abs(Data.ComponentR) <= 0.001f)
		{
			YIntercept[0] = 0;
			YIntercept[1] = INFINITY;
			return true;
		}

		return false;
	}

	YIntercept[0] = 0;
	YIntercept[1] = GetY(Data, 0);
	return true;
}

FString
UBPL_LinearFormula::ToString(
	const FLinearData& Data
) noexcept
{
	return FString::Printf(TEXT("%fx + %fy = %f"),
		Data.ComponentP, Data.ComponentQ, Data.ComponentR);
}

void
UBPL_LinearFormula::WithAB(
	FLinearData& Data,
	const float A,
	const float B
) noexcept
{
	SetSlope(Data, A);
	Data.ComponentR = B;
}
