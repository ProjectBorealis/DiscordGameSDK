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
	static bool Initialize(int64 ClientID);
	static bool RunCallbacks();
};
