// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SF_StageInfo.generated.h"

class ASF_EnemyBase;

//////////
// enemy group
USTRUCT(BlueprintType)
struct FSF_EnemyGroup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASF_EnemyBase> EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 EnemyCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EnemyPos;
};


//////////
// wave
USTRUCT(BlueprintType)
struct FSF_WaveSetting
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSF_EnemyGroup> EnemyGroup;
};

///////////
/// stageInfo
USTRUCT(BlueprintType)
struct SKYFLOWER_API FSF_StageInfo : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSF_WaveSetting> WaveSetting;
};





