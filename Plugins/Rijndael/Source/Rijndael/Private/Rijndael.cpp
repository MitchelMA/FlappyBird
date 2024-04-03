// Copyright Epic Games, Inc. All Rights Reserved.

#include "Rijndael.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FRijndaelModule"

DEFINE_LOG_CATEGORY(LogRijndael);

void FRijndaelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	const auto LibPath = FPaths::Combine(IPluginManager::Get().FindPlugin("Rijndael")->GetBaseDir(), "Lib");
	Rijndael_DLL_Handle = FPlatformProcess::GetDllHandle(*FPaths::Combine(LibPath, "Rijndael.dll"));

	if (Rijndael_DLL_Handle != nullptr)
	{
		UE_LOG(LogRijndael, Log,
			TEXT("Successfully loaded handle `Rijndael.dll` for plugin"));
	}
	else
	{
		UE_LOG(LogRijndael, Error,
			TEXT("Failed trying to load handle `Rijndael.dll` for plugin"));	
	}
}

void FRijndaelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (Rijndael_DLL_Handle == nullptr)
		return;
	
	FPlatformProcess::FreeDllHandle(Rijndael_DLL_Handle);
	Rijndael_DLL_Handle = nullptr;
	UE_LOG(LogRijndael, Log, TEXT("Successfully unloaded handle for Rijndael.dll"))
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRijndaelModule, Rijndael)