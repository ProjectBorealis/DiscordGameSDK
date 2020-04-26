// Copyright 2019 Daniel Butum

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/CoreOnline.h"


#include "DiscordHelper.generated.h"

UCLASS()
class DISCORDGAMESDK_API UDiscordHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool Initialize(int64 ClientID, bool bDiscordRequired = false);
	static bool RunCallbacks();

	//
	// Activities
	// https://discordapp.com/developers/docs/game-sdk/activities
	//
	
	static bool UpdatePlayActivity(const FString& State, const FString& Details);
	static bool RegisterSteam(uint32 SteamAppID);
};
