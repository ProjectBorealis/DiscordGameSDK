// Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;
using Tools.DotNETCommon;

public class DiscordGameSDK : ModuleRules
{
	public DiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;
		PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");

		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
		// PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty", "Discord"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DiscordGameSDKLibrary"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Projects",
			}
		);
		// string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Source", "ThirdParty", "DiscordGameSDKLibrary"));
		// PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));
		// PrivateIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));
	}

}
