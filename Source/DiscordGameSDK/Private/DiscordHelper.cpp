// Copyright 2019 Daniel Butum

#pragma once

#include "DiscordHelper.h"

#include "DiscordLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogDiscord, All, All)


static discord::Core* Core = nullptr;


bool UDiscordHelper::Initialize(int64 ClientID)
{
	// https://discordapp.com/developers/docs/game-sdk/sdk-starter-guide#code-primer-unreal-engine-4-cpp
	discord::Result result = discord::Core::Create(ClientID, DiscordCreateFlags_Default, &Core);
	if (result != discord::Result::Ok || Core == nullptr)
	{
		UE_LOG(LogDiscord, Error, TEXT("Failed to create Discord Core"));
		return false;
	}
	
	discord::Activity activity{};
	activity.SetState("Testing");
	activity.SetDetails("Fruit Loops");
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

bool UDiscordHelper::RunCallbacks()
{
	if (Core)
		return Core->RunCallbacks() == discord::Result::Ok;

	return false;
}
