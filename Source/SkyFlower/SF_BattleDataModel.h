// ==================================================
// Filename	:	SF_BattleDataModel.h
// Author	:	22cu0105 ���c���Ől
// Description: �o�g���f�[�^�\��
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SF_BattleDataModel.generated.h"

class ASF_EnemyBase;

// ��������G�̏��
USTRUCT(BlueprintType)
struct FSF_GeneratEnemyInfo
{
	GENERATED_BODY()

public:
	// ��������G�l�~�[(BP)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASF_EnemyBase> EnemyChara;

	// ���������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 MaxGenerateNum;
	// �������W
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> SpawnPosList;

public:
	FSF_GeneratEnemyInfo()
		: EnemyChara(nullptr)
		, MaxGenerateNum(0)
		, SpawnPosList()
	{}
};

// �X�e�[�W���̃t�F�[�Y�̏��
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

// �X�e�[�W�̏��
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

	//// �f�[�^��荞�ݗp�t�@���N�V����
	//UFUNCTION(CallInEditor)
	//void LoadData();
};