#pragma once

#include "CoreMinimal.h"
#include "LinearIntersectionType.generated.h"

UENUM(BlueprintType)
enum ELinearIntersectionType
{
	None,
	Once,
	Continuous
};
