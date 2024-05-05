// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_FunctionLibrary.h"
#include "SF_GameMode.h"
#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"


ASF_GameMode* USF_FunctionLibrary::GetGameMode(UObject* WorldContextObject)
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

ASF_Player* USF_FunctionLibrary::GetPlayer(UObject* WorldContextObject, int32 PlayerIndex)
{
	return Cast<ASF_Player>(UGameplayStatics::GetPlayerPawn(WorldContextObject, PlayerIndex));
}

ASF_EnemyBase* USF_FunctionLibrary::SpawnAIEnemy(UObject* const WorldContextObject, const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemyChara, UBehaviorTree* const InBehaviorTree)
{
	return Cast<ASF_EnemyBase>(UAIBlueprintHelperLibrary::SpawnAIFromClass(WorldContextObject, InEnemyChara, InBehaviorTree, InLocation));
}