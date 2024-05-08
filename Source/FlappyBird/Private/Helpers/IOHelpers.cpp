#include "Helpers/IOHelpers.h"
#include "Structs/ScoreTable.h"
#include "JsonObjectConverter.h"
#include "RijndaelBPLibrary.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogIOHelper)

FString UIOHelpers::SaveDirectory = FPaths::Combine(*FPaths::ProjectDir(), TEXT("SaveDir"));
static FString GetKey() noexcept;

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

	TArray<uint8> CipherBytes;
	bool EncryptionSuccess = false;
	URijndaelBPLibrary::Encrypt(JsonString, GetKey(), EncryptionSuccess, CipherBytes);
	
	if (!EncryptionSuccess)
	{
		Success = false;
		return;
	}

	FFileHelper FileHelper = {};
	const FString FullSaveFileName = FPaths::Combine(SaveDirectory, FileName);
	if ((Success = FileHelper.SaveArrayToFile(CipherBytes, *FullSaveFileName)) == true)
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

	TArray<uint8> CipherBytes;
	if (!FileHelper.LoadFileToArray(CipherBytes, *FullSaveFileName))
	{
		Success = false;
		return;
	}

	FString JsonText;
	bool DecryptionSuccess = false;
	URijndaelBPLibrary::Decrypt(CipherBytes, GetKey(), DecryptionSuccess, JsonText);
	if (!DecryptionSuccess)
	{
		Success = false;
		return;
	}

	Success = FJsonObjectConverter::JsonObjectStringToUStruct<FScoreTable>(JsonText, &ScoreTable);
}

FString
GetKey()
noexcept
{
	FString ProjectId;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectID"),
		ProjectId,
		GGameIni);
	return UGameplayStatics::GetPlatformName() + UKismetSystemLibrary::GetPlatformUserName() + ProjectId;
}
