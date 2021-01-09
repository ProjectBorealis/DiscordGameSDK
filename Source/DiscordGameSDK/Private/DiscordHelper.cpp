// Copyright 2019 Daniel Butum

#pragma once

#include "DiscordHelper.h"
#include "DiscordLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogDiscord, All, All)


static discord::Core* Core = nullptr;


bool UDiscordHelper::Initialize(int64 ClientID, bool bDiscordRequired)
{
	// https://discordapp.com/developers/docs/game-sdk/sdk-starter-guide#code-primer-unreal-engine-4-cpp
	const discord::Result Result = discord::Core::Create(ClientID, bDiscordRequired ? DiscordCreateFlags_Default : DiscordCreateFlags_NoRequireDiscord, &Core);
	if (Result != discord::Result::Ok || Core == nullptr)
	{
		UE_LOG(LogDiscord, Error, TEXT("Failed to create Discord Core"));
		return false;
	}

	discord::Event<> OnUserConnectedEvent;
	auto UserConnectionHandler = [&]()
	{
		if (Core)
		{
			discord::User CurrentUser;
			const discord::Result UserResult = Core->UserManager().GetCurrentUser(&CurrentUser);
			if (UserResult == discord::Result::Ok)
			{
				OnUserConnected.Broadcast(CurrentUser.GetUsername(), CurrentUser.GetId(), CurrentUser.GetDiscriminator());
			}
		}
	};

	OnUserConnectedEvent.Connect(UserConnectionHandler);
	Core->UserManager().OnCurrentUserUpdate = OnUserConnectedEvent;

	return true;
}

bool UDiscordHelper::RunCallbacks() const
{
	if (Core)
	{
		return Core->RunCallbacks() == discord::Result::Ok;
	}
	return false;
}

int64 UDiscordHelper::GetConnectedUserID()
{
	if (Core)
	{
		discord::User CurrentUser;
		const discord::Result Result = Core->UserManager().GetCurrentUser(&CurrentUser);
		if (Result == discord::Result::Ok)
		{
			return CurrentUser.GetId();
		}
	}
	return 0;
}

FString UDiscordHelper::GetConnectedUserName()
{
	if (Core)
	{
		discord::User CurrentUser;
		const discord::Result Result = Core->UserManager().GetCurrentUser(&CurrentUser);
		if (Result == discord::Result::Ok)
		{
			return CurrentUser.GetUsername();
		}
	}
	return "Unknown Discord User";
}

bool UDiscordHelper::UpdatePlayActivity(const FString& Details, const FString& State, int64 Timestamp)
{
	if (!Core)
	{
		return false;
	}

	discord::Activity activity{};
	activity.SetType(discord::ActivityType::Playing);
	activity.SetState(TCHAR_TO_ANSI(*State));
	activity.SetDetails(TCHAR_TO_ANSI(*Details));
	activity.GetAssets().SetLargeImage("pretty-cover");
	activity.GetAssets().SetSmallImage("logo-sq-b");
	discord::ActivityTimestamps& Timestamps = activity.GetTimestamps();
	Timestamps.SetStart(Timestamp);
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

void UDiscordHelper::ClearPlayActivity()
{
	if (Core)
	{
		Core->ActivityManager().ClearActivity([](discord::Result){});
	}
}

void UDiscordHelper::ValidateOrExit(std::function<void(discord::Result)> Callback)
{
	if (Core)
	{
		Core->ApplicationManager().ValidateOrExit(Callback);
	}
}

bool UDiscordHelper::RegisterSteam(uint32 SteamAppID)
{
	if (!Core)
	{
		return false;
	}

	return Core->ActivityManager().RegisterSteam(SteamAppID) == discord::Result::Ok;
}
