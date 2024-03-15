#include "IOHelpers.h"

DEFINE_LOG_CATEGORY(LogIOHelper)

FString UIOHelpers::SaveDirectory = FPaths::Combine(*FPaths::ProjectDir(), TEXT("SaveDir"));

void
UIOHelpers::SaveData(
	FString FileName,
	bool& Success,
	FString& SaveName
)
{

	FFileHelper FileHelper = {};

	const FString FullSaveFileName = FPaths::Combine(SaveDirectory, FileName);

	if ((Success = FileHelper.SaveStringToFile(
		FString("Test"), *FullSaveFileName
	)) == true)
	{
		SaveName = FullSaveFileName;
		UE_LOG(LogIOHelper, Log, TEXT("Saved Data to %s"), *SaveDirectory);
	}
}
