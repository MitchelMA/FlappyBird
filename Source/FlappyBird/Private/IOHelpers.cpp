#include "IOHelpers.h"
#include "ScoreTable.h"
#include "JsonObjectConverter.h"

DEFINE_LOG_CATEGORY(LogIOHelper)

FString UIOHelpers::SaveDirectory = FPaths::Combine(*FPaths::ProjectDir(), TEXT("SaveDir"));

void
UIOHelpers::SaveScore(
	FString FileName,
	const FScoreTable& ScoreTable,
	bool& Success,
	FString& FullOutputName
)
{
	FString JsonString;
	if(!FJsonObjectConverter::UStructToJsonObjectString(ScoreTable, JsonString, 0, 0, 0, nullptr, false))
	{
		Success = false;
		return;
	}

	FFileHelper FileHelper = {};
	const FString FullSaveFileName = FPaths::Combine(SaveDirectory, FileName);
	if ((Success = FileHelper.SaveStringToFile(JsonString, *FullSaveFileName)) == true)
		FullOutputName = FullSaveFileName;
}

void
UIOHelpers::LoadScore(
	FString Filename,
	bool& Success,
	FScoreTable& ScoreTable
)
{
	FFileHelper FileHelper = {};
	const FString FullSaveFileName = FPaths::Combine(SaveDirectory, Filename);
	if (!FPaths::FileExists(FullSaveFileName))
	{
		Success = false;
		return;
	}

	FString JsonString;
	if (!FileHelper.LoadFileToString(JsonString, *FullSaveFileName))
	{
		Success = false;
		return;
	}

	Success = FJsonObjectConverter::JsonObjectStringToUStruct<FScoreTable>(JsonString, &ScoreTable);
}
