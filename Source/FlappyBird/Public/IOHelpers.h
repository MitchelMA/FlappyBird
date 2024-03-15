#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IOHelpers.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogIOHelper, Log, All);

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API UIOHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static FString SaveDirectory;

public:

	UFUNCTION(BlueprintCallable)
	static void SaveData(FString FileName, bool& Success, FString& SaveName);
};
