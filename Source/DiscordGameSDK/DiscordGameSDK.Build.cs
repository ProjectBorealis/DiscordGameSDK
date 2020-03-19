// Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class DiscordGameSDK : ModuleRules
{
    public DiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");

		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
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
				"DiscordGameSDKLibrary"
            }
		);
        string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Source", "ThirdParty", "DiscordGameSDKLibrary"));
		PublicIncludePaths.Add( Path.Combine( BaseDirectory, "Include" ) );
		PrivateIncludePaths.Add( Path.Combine( BaseDirectory, "Include" ) );

	}
}