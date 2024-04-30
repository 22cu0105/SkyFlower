// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_FunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SF_GameMode.h"
#include "SF_Player.h"


ASF_GameMode* USF_FunctionLibrary::GetGameMode(UObject* WorldContextObject)
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

ASF_Player* USF_FunctionLibrary::GetPlayer(UObject* WorldContextObject, int32 PlayerIndex)
{
	return Cast<ASF_Player>(UGameplayStatics::GetPlayerPawn(WorldContextObject, PlayerIndex));
}

