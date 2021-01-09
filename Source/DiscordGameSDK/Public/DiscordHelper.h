// Copyright 2019 Daniel Butum

#pragma once

#include "CoreMinimal.h"

#include "types.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiscordHelper.generated.h"

UCLASS()
class DISCORDGAMESDK_API UDiscordHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	bool Initialize(int64 ClientID, bool bDiscordRequired = false);
	bool RunCallbacks() const;

	//
	// Activities
	// https://discordapp.com/developers/docs/game-sdk/activities
	//

	static int64 GetConnectedUserID();
	static FString GetConnectedUserName();
	static bool UpdatePlayActivity(const FString& Details, const FString& State, int64 Timestamp);
	static void ClearPlayActivity();
	static void ValidateOrExit(std::function<void(discord::Result)> Callback);
	static bool RegisterSteam(uint32 SteamAppID);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUserConnectedSignature, const FString&, UserName, const int64, UserId, const FString&, UserDiscriminator);
	UPROPERTY(BlueprintAssignable)
	FOnUserConnectedSignature OnUserConnected;
};
