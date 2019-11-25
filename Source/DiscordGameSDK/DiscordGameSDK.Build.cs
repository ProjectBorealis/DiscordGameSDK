// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class DiscordGameSDK : ModuleRules
{
    public DiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        Definitions.Add("DISCORD_DYNAMIC_LIB=1");

        PublicIncludePaths.AddRange(
            new string[] {
                "DiscordGameSDK/Public"
            }
		);

        PrivateIncludePaths.AddRange(
            new string[] {
                "DiscordGameSDK/Private"
            }
		);

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
                "Projects"
            }
		);

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
		);

        string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Source", "ThirdParty", "DiscordGameSDKLibrary"));
		PublicIncludePaths.Add(Path.Combine(BaseDirectory, "Include"));
    }
}