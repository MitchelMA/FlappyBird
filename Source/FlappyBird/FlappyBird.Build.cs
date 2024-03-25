// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FlappyBird : ModuleRules
{
	public FlappyBird(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Paper2D", "JsonUtilities", "Json", "UMG"});
	}
}
