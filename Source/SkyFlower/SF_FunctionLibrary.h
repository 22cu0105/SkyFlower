// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SF_FunctionLibrary.generated.h"

class ASF_GameMode;
class ASF_Player;
class ASF_MainCamera;

UCLASS()
class SKYFLOWER_API USF_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "SkyFlower")
	static ASF_GameMode* GetGameMode(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "SkyFlower")
	static ASF_Player* GetPlayer(UObject* WorldContextObject, int32 PlayerIndex = 0);

};
