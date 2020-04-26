// Copyright 2019 Daniel Butum

#pragma once

#include "DiscordHelper.h"

#include "DiscordLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogDiscord, All, All)


static discord::Core* Core = nullptr;


bool UDiscordHelper::Initialize(int64 ClientID, bool bDiscordRequired)
{
	// https://discordapp.com/developers/docs/game-sdk/sdk-starter-guide#code-primer-unreal-engine-4-cpp
	discord::Result result = discord::Core::Create(ClientID, bDiscordRequired ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord, &Core);
	if (result != discord::Result::Ok || Core == nullptr)
	{
		UE_LOG(LogDiscord, Error, TEXT("Failed to create Discord Core"));
		return false;
	}
	
	return true;
}

bool UDiscordHelper::RunCallbacks()
{
	if (Core)
		return Core->RunCallbacks() == discord::Result::Ok;

	return false;
}

bool UDiscordHelper::UpdatePlayActivity(const FString& State, const FString& Details)
{
	if (!Core)
		return false;

	discord::Activity activity{};
	activity.SetType(discord::ActivityType::Playing);
	activity.SetState(TCHAR_TO_ANSI(*State));
	activity.SetDetails(TCHAR_TO_ANSI(*Details));
	Core->ActivityManager().UpdateActivity(activity, [](discord::Result result)
	{
		if (result != discord::Result::Ok)
		{
			UE_LOG(LogDiscord, Log, TEXT("Discord Activity Fail"));
			return;
		}

		UE_LOG(LogDiscord, Log, TEXT("Discord Activity Set"));
	});

	return true;
}

bool UDiscordHelper::RegisterSteam(uint32 SteamAppID)
{
	if (!Core)
		return false;

	return Core->ActivityManager().RegisterSteam(SteamAppID) == discord::Result::Ok;
}