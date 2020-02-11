// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class DiscordGameSDKLibrary : ModuleRules
	{
		public DiscordGameSDKLibrary(ReadOnlyTargetRules Target) : base(Target)
		{
			Type = ModuleType.External;
            PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");

            string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "DiscordGameSDKLibrary"));

			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				string lib = Path.Combine(BaseDirectory, "Win64");

				// Include headers
				PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));

				// Add the import library
				PublicAdditionalLibraries.Add(lib);

				// Dynamic
				RuntimeDependencies.Add(Path.Combine(lib, "discord_game_sdk.dll"));
				PublicDelayLoadDLLs.Add("discord_game_sdk.dll");
			}
			else if (Target.Platform == UnrealTargetPlatform.Linux)
			{
				string lib = Path.Combine(BaseDirectory, "Linux", "x86_64-unknown-linux-gnu");

				// Include headers
				PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));

				// Add the import library
				PublicAdditionalLibraries.Add(lib);
				RuntimeDependencies.Add(Path.Combine(lib, "discord_game_sdk.so"));
			}
			else if (Target.Platform == UnrealTargetPlatform.Mac)
			{
				string lib = Path.Combine(BaseDirectory, "Mac");

				// Include headers
				PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));

				// Add the import library
				PublicAdditionalLibraries.Add(lib);
				RuntimeDependencies.Add(Path.Combine(lib, "discord_game_sdk.dylib"));
			}
		}
	}
}
