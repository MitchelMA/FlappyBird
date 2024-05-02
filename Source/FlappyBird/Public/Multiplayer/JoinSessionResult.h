#pragma once

#include "CoreMinimal.h"

UENUM(Blueprintable, BlueprintType)
enum EJoinSessionResult
{
	Success,
	SessionIsFull,
	SessionDoesNotExist,
	CouldNotRetrieveAddress,
	AlreadyInSession,
	UnknownError
};
