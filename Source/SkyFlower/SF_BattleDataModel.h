// ==================================================
// Filename	:	SF_BattleDataModel.h
// Author	:	22cu0105 小田島稜人
// Description: バトルデータ構造
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SF_BattleDataModel.generated.h"

class ASF_EnemyBase;

// 生成する敵の情報
USTRUCT(BlueprintType)
struct FSF_GeneratEnemyInfo
{
	GENERATED_BODY()

public:
	// 生成するエネミー(BP)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASF_EnemyBase> EnemyChara;

	// 生成上限数
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 MaxGenerateNum;
	// 生成座標
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> SpawnPosList;

public:
	FSF_GeneratEnemyInfo()
		: EnemyChara(nullptr)
		, MaxGenerateNum(0)
		, SpawnPosList()
	{}
};

// ステージ毎のフェーズの情報
USTRUCT(BlueprintType)
struct FSF_WaveInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSF_GeneratEnemyInfo> GenerateEnemyList;

public:
	FSF_WaveInfo()
		: GenerateEnemyList()
	{}
};

// ステージの情報
USTRUCT(BlueprintType)
struct FSF_BattleStageInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSF_WaveInfo> WaveInfoList;

public:
	FSF_BattleStageInfo()
		: WaveInfoList()
	{}
};

UCLASS()
class SKYFLOWER_API USF_BattleDataModel : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USF_BattleDataModel();

	UPROPERTY(EditAnywhere, Category = "BattleData Setting")
	TMap<uint8, FSF_BattleStageInfo> BattleDataMap;

	//// データ取り込み用ファンクション
	//UFUNCTION(CallInEditor)
	//void LoadData();
};