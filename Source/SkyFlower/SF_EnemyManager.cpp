#include "SF_EnemyManager.h"
#include "SF_EnemyGenerator.h"
#include "SF_EnemyBase.h"


USF_EnemyManager::USF_EnemyManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	EnemyGenerator = CreateDefaultSubobject<USF_EnemyGenerator>(TEXT("EnemyGenerator"));
}

void USF_EnemyManager::BeginPlay()
{
	Super::BeginPlay();

}

void USF_EnemyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �Ǘ����Ă���G�����S���Ă��邩�Ď�����
	// ���S���Ă�����̈���������
	for (ASF_EnemyBase* DestroyEnemy : TryGetDeadEnemies())
	{
		if (EnemyList.Contains(DestroyEnemy))
			EnemyList.Remove(DestroyEnemy);
	}
}

/// @brief SpawnType�Ő������@�𕪂���
/// @param InSpawnType 
/// @param InLocation 
/// @param InEnemy 
/// @param InNum 
void USF_EnemyManager::SpawnAIEnemyFromGenerationType(const ESF_SpawnType InSpawnType, const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemy, const int InNum)
{
	switch (InSpawnType)
	{
	case ESF_SpawnType::Normal:
		//NormalAIEnemySpawn();
		break;
	case ESF_SpawnType::FlockEnemy:
		break;
	}
}

FVector USF_EnemyManager::GetNearestEnemyPos(const FVector& InLocation)
{
	FVector NearestEnemyPos = InLocation;

	for (ASF_EnemyBase* CheackEnemy : EnemyList)
	{
		if (!IsValid(CheackEnemy)) continue;

		const FVector EnemyPos = CheackEnemy->GetActorLocation();
		const float CurrentLength = (InLocation - EnemyPos).Size();
		const float PrevLength = NearestEnemyPos.Size();

		if (CurrentLength < PrevLength)
			NearestEnemyPos = EnemyPos;
	}

	return NearestEnemyPos;
}

/// @brief ���S���Ă���G�L�����N�^�[���擾
/// @return ���S���Ă���G�̔z��
TArray<ASF_EnemyBase*> USF_EnemyManager::TryGetDeadEnemies() const
{
	// ���S���Ă���G�̃A�h���X�i�[�p
	TArray<ASF_EnemyBase*> DeadEnemyList;

	for (ASF_EnemyBase* CheackEnemy : EnemyList)
	{
		if (!IsValid(CheackEnemy)) continue;

		// ���S���Ă��邩���肵�A�z��ɒǉ�
		if (CheackEnemy->IsDead())
			DeadEnemyList.Add(CheackEnemy);
	}

	return DeadEnemyList;
}

/// @brief �ʏ�G�̐�������
/// @param InEnemy 
/// @param InLocation 
/// @param InNum 
void USF_EnemyManager::NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// ����������������
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}

/// @brief �Q�O�G�̐�������
/// @param InEnemy 
/// @param InLocation 
/// @param InNum 
void USF_EnemyManager::FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList;

	// �������W�b�N�������ɏ���

	CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// ����������������
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}