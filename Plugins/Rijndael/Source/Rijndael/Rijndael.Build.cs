// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class Rijndael : ModuleRules
{
	public Rijndael(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		var rijndaelLibPath = Path.GetFullPath(Path.Combine(ModuleDirectory, @"..\..\Lib"));
		Console.WriteLine($"Rijndael-lib dir: {rijndaelLibPath}");
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Projects"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		PublicDelayLoadDLLs.Add("Rijndael.dll");
		PublicAdditionalLibraries.Add(Path.Combine(rijndaelLibPath, "Rijndael.lib"));
		if (Target.Platform == UnrealTargetPlatform.Win64)
			RuntimeDependencies.Add(Path.Combine(rijndaelLibPath, "Rijndael.dll"));
	}
}
