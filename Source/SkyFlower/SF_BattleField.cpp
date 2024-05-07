#include "SF_BattleField.h"
#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "SF_GameMode.h"
#include "SF_EnemyManager.h"
#include "SF_BattleDataModel.h"
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

	// ������
	FieldEventType = ESF_FieldEventType::Waiting;
	BattleStageInfo = GetBattleStageData();
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

FSF_BattleStageInfo ASF_BattleField::GetBattleStageData() const
{
	FSF_BattleStageInfo OutBattleStageInfo = FSF_BattleStageInfo();

	if (BattleDataAsset == nullptr) return OutBattleStageInfo;

	if (auto BattleDataModel = Cast<USF_BattleDataModel>(StaticLoadObject(USF_BattleDataModel::StaticClass(), nullptr, *BattleDataAsset.ToString())))
		if (auto BattleStageData = BattleDataModel->BattleDataMap.Find(StageID))
			OutBattleStageInfo = *BattleStageData;

	return OutBattleStageInfo;
}

void ASF_BattleField::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �v���C���[���g���K�[�{�b�N�X�ɓ�������o�g���J�n
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

	// �ꊇ�Ő����������s��
	SpawnAllEnemiesInWave(CurrentWaveCnt);
	// �ǐ��������Ȃǂ��s�����Ƃ��o����
}

void ASF_BattleField::UpdateOnActive(const float InDeltaTime)
{
	ASF_GameMode* const SF_GameMode = USF_FunctionLibrary::GetGameMode(GetWorld());
	if (!IsValid(SF_GameMode)) return;

	// ToDo	�G�̊Ǘ��\����ύX���邩��
	// ���݂̃t�F�[�Y�̓G�����ׂē|������
	if (StageEnemyList.Num() <= 0)
	{
		CurrentWaveCnt++;
		// ���݂̃E�F�[�u���Ō�̃E�F�[�u��葽�����
		if (CurrentWaveCnt >= BattleStageInfo.WaveInfoList.Num())
		{
			// �I������
			ESF_FieldEventType::Inactive;
			Debug::Print("BattleField : EndBattleStage");
			return;
		}

		// �ꊇ�Ő����������s��
		SpawnAllEnemiesInWave(CurrentWaveCnt);
	}
}

/// @brief �E�F�[�u�ɑΉ�����G��S�Đ�������
/// @param InWaveCnt 
void ASF_BattleField::SpawnAllEnemiesInWave(const int InWaveCnt)
{
	ASF_GameMode* const SF_GameMode = USF_FunctionLibrary::GetGameMode(GetWorld());
	if (!IsValid(SF_GameMode)) return;
	USF_EnemyManager* SF_EnemyManager = SF_GameMode->GetEnemyManager();
	if (!IsValid(SF_EnemyManager)) return;


	const FSF_WaveInfo WaveInfo = BattleStageInfo.WaveInfoList[InWaveCnt];
	// ��������G�̎�ޕ��������s��
	for (int et_i = 0; et_i < WaveInfo.GenerateEnemyList.Num(); et_i++)
	{
		const FSF_GeneratEnemyInfo EnemyInfo = WaveInfo.GenerateEnemyList[et_i];
		// ��������G�̐������������s��
		for (int e_i = 0; e_i < EnemyInfo.MaxGenerateNum; e_i++)
		{
			if (!IsValid(EnemyInfo.EnemyChara)) continue;

			ASF_EnemyBase* const CreateEnemy =
			USF_FunctionLibrary::SpawnAIEnemy(
				/*WorldContext = */GetWorld(),
				/*Location	   = */EnemyInfo.SpawnPosList[e_i],
				/*EnemyChara   = */EnemyInfo.EnemyChara);

			StageEnemyList.Add(CreateEnemy);
			SF_GameMode->GetEnemyManager()->AddEnemy(CreateEnemy);
		}
	}
}