// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class RIJNDAEL_API FRijndaelModule : public IModuleInterface
{
	void* Rijndael_DLL_Handle = nullptr;
	
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
