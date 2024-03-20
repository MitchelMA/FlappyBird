#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IOHelpers.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogIOHelper, Log, All);

struct FScoreTable;


UCLASS()
class FLAPPYBIRD_API UIOHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static FString SaveDirectory;

public:

	UFUNCTION(BlueprintCallable)
	static void SaveScore(FString FileName, const FScoreTable& ScoreTable, bool& Success, FString& FullOutputName);
	UFUNCTION(BlueprintCallable)
	static void LoadScore(FString Filename, bool& Success, FScoreTable& ScoreTable);
	
};
