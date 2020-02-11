// Copyright 1998-2020 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class DiscordGameSDK : ModuleRules
{
    public DiscordGameSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDefinitions.Add("DISCORD_DYNAMIC_LIB=1");

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

        string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Source", "ThirdParty", "DiscordGameSDKLibrary"));
		PublicAdditionalLibraries.Add(Path.Combine(BaseDirectory, "Include"));
    }
}