#pragma once

#include "CoreMinimal.h"
#include "ScoreTable.generated.h"


USTRUCT(Blueprintable)
struct FLAPPYBIRD_API FScoreTable
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 HighScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 LastScore;

	FScoreTable()
	{
		HighScore = 0;
		LastScore = 0;
	}
};
