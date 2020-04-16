// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DiscordGameSDK.h"

#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FDiscordGameSDKModule"

void FDiscordGameSDKModule::StartupModule()
{
#if !PLATFORM_LINUX
#if defined(DISCORD_DYNAMIC_LIB)
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("DiscordGameSDK")->GetBaseDir();
	const FString SDKDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("DiscordGameSDKLibrary"));
#if PLATFORM_WINDOWS
	const FString LibName = TEXT("discord_game_sdk");
	const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Win64"));
	if (!LoadDependency(LibDir, LibName, DiscordGameSDKLibraryHandle))
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load DiscordGameSDK plugin. Plug-in will not be functional."));
		FreeDependency(DiscordGameSDKLibraryHandle);
	}
#elif PLATFORM_MAC
	const FString LibName = TEXT("discord_game_sdk");
	const FString LibDir = FPaths::Combine(*SDKDir, TEXT("Mac"));
	if (!LoadDependency(LibDir, LibName, DiscordRpcLibraryHandle))
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT(LOCTEXT_NAMESPACE, "Failed to load DiscordGameSDK plugin. Plug-in will not be functional."));
		FreeDependency(DiscordGameSDKLibraryHandle);
	}
#endif
#endif
#endif
}

void FDiscordGameSDKModule::ShutdownModule()
{
	// Free the dll handle
#if !PLATFORM_LINUX
#if defined(DISCORD_DYNAMIC_LIB)
	FreeDependency(DiscordGameSDKLibraryHandle);
#endif
#endif
}

bool FDiscordGameSDKModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{
		return false;
	}

	return true;
}

void FDiscordGameSDKModule::FreeDependency(void*& Handle)
{
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDiscordGameSDKModule, DiscordGameSDK)