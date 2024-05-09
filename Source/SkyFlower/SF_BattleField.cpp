#include "SF_BattleField.h"
#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "SF_GameMode.h"
#include "SF_EnemyManager.h"
#include "SF_StageDataModel.h"
#include "SF_FunctionLibrary.h"
#include "DebugHelpers.h"
#include "Components/BoxComponent.h"

ASF_BattleField::ASF_BattleField()
	: StageID(0)
	, StageEnemyList()
	, CurrentWaveCnt(0)
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ASF_BattleField::OnBeginOverlap);
}

void ASF_BattleField::BeginPlay()
{
	Super::BeginPlay();

	// 初期化
	FieldEventType = ESF_FieldEventType::Waiting;
	BattleStageInfo = GetBattleStageData(StageID);
}

void ASF_BattleField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<ASF_EnemyBase*> DeadEnemyList;
	for (ASF_EnemyBase* CheackEnemy : StageEnemyList)
	{
		if (!IsValid(CheackEnemy))
			DeadEnemyList.Add(CheackEnemy);
	}

	for (ASF_EnemyBase* DestroyEnemy : DeadEnemyList)
	{
		if (StageEnemyList.Contains(DestroyEnemy))
			StageEnemyList.Remove(DestroyEnemy);
	}


	if (FieldEventType != ESF_FieldEventType::Active) return;

	UpdateOnActive(DeltaTime);
}

/// @brief DataAssetからデータを取得する
/// @return StageIDに対応したステージ情報構造体
FSF_StageInfo ASF_BattleField::GetBattleStageData(const uint8 InStageID) const
{
	FSF_StageInfo OutBattleStageInfo = FSF_StageInfo();

	if (StageDataAsset == nullptr)
	{
		Debug::Print("not found 'StageDataAsset'");
		return OutBattleStageInfo;
	}

	if (const USF_StageDataModel* const BattleDataModel = Cast<USF_StageDataModel>(StaticLoadObject(USF_StageDataModel::StaticClass(), nullptr, *StageDataAsset.ToString())))
		if (const FSF_StageInfo* const BattleStageData = BattleDataModel->StageDataMap.Find(InStageID))
			OutBattleStageInfo = *BattleStageData;

	return OutBattleStageInfo;
}

void ASF_BattleField::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// プレイヤーがトリガーボックスに入ったらバトル開始
	if (Cast<ASF_Player>(OtherActor))
	{
		Debug::Print("BattleField : OnBeginOverlap : Player");
		OnPlayerEnterBattleField();
	}
}

void ASF_BattleField::OnPlayerEnterBattleField()
{
	if (FieldEventType != ESF_FieldEventType::Waiting) return;

	FieldEventType = ESF_FieldEventType::Active;

	// 一括で生成処理を行う
	SpawnAllEnemiesInWave(CurrentWaveCnt);
	// 壁生成処理などを行うことが出来る
}

void ASF_BattleField::UpdateOnActive(const float InDeltaTime)
{
	const ASF_GameMode* const SF_GameMode = USF_FunctionLibrary::GetGameMode(GetWorld());
	if (!IsValid(SF_GameMode)) return;

	// ToDo	敵の管理構造を変更するかも
	// 現在のフェーズの敵をすべて倒したら
	if (StageEnemyList.Num() <= 0)
	{
		CurrentWaveCnt++;
		// 現在のウェーブが最後のウェーブより多ければ
		if (CurrentWaveCnt >= BattleStageInfo.WaveSetting.Num())
		{
			// 終了処理
			ESF_FieldEventType::Inactive;
			Debug::PrintFixedLine("BattleField : EndBattleStage");
			return;
		}

		// 一括で生成処理を行う
		SpawnAllEnemiesInWave(CurrentWaveCnt);
	}
}

/// @brief ウェーブに対応する敵を全て生成する
/// @param InWaveCnt 
void ASF_BattleField::SpawnAllEnemiesInWave(const int InWaveCnt)
{
	const ASF_GameMode* const SF_GameMode = USF_FunctionLibrary::GetGameMode(GetWorld());
	if (!IsValid(SF_GameMode)) return;
	USF_EnemyManager* const SF_EnemyManager = SF_GameMode->GetEnemyManager();
	if (!IsValid(SF_EnemyManager)) return;


	const FSF_WaveSetting WaveInfo = BattleStageInfo.WaveSetting[InWaveCnt];
	// 生成する敵の配列分処理を行う
	for (int et_i = 0; et_i < WaveInfo.EnemyGroup.Num(); et_i++)
	{
		const FSF_EnemyGroup EnemyInfo = WaveInfo.EnemyGroup[et_i];
		if (!IsValid(EnemyInfo.EnemyType)) continue;
		// 生成する敵の数だけ処理を行う
		for (int e_i = 0; e_i < EnemyInfo.EnemyCount; e_i++)
		{
			Debug::Print("BattleField : Spawn()");

			ASF_EnemyBase* const CreateEnemy =
			USF_FunctionLibrary::SpawnAIEnemy(
				/*WorldContext = */GetWorld(),
				/*Location	   = */EnemyInfo.EnemyPos,
				/*EnemyChara   = */EnemyInfo.EnemyType);

			StageEnemyList.Add(CreateEnemy);
			SF_GameMode->GetEnemyManager()->AddEnemy(CreateEnemy);
		}
	}
}