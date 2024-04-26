#include "SF_EnemyManager.h"
#include "SF_EnemyGenerator.h"
#include "SF_EnemyBase.h"
#include "Kismet/GameplayStatics.h"


USF_EnemyManager::USF_EnemyManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	EnemyGenerator = CreateDefaultSubobject<USF_EnemyGenerator>(TEXT("EnemyGenerator"));
}

void USF_EnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// ���O�Ƀ}�b�v��ɓG���z�u����Ă���G���������A�i�[
	// �f�o�b�O�p�B���ۂ͎��O�Ƀ}�b�v��ɓG�����邱�Ƃ͌����ĂȂ�
	TArray<AActor*> PrevSpawnedEnemyList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASF_EnemyBase::StaticClass(), PrevSpawnedEnemyList);
	for (AActor* EnemyActor : PrevSpawnedEnemyList)
	{
		if (!IsValid(EnemyActor)) continue;

		EnemyList.Add(Cast<ASF_EnemyBase>(EnemyActor));
	}
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

/// @brief �����œn���ꂽ���W�Ɉ�ԋ߂��G�̍��W���擾
/// @param InLocation ��r������W
/// @return 
ASF_EnemyBase* USF_EnemyManager::GetNearestEnemyPos(const FVector& playerLocation)
{
	//init
	ASF_EnemyBase* OutNearestEnemy = nullptr;
	FVector PrevNearestEnemyPos = playerLocation;

	//find target in EnemyList
	for (ASF_EnemyBase* CheackEnemy : EnemyList)
	{
		//if null return
		if (!IsValid(CheackEnemy)) continue;

		//get distance for this enemy
		const FVector EnemyPos = CheackEnemy->GetActorLocation();
		const float CurrentLength = (playerLocation - EnemyPos).Size();
		const float PrevLength = PrevNearestEnemyPos.Size();

		if (CurrentLength < PrevLength)
		{
			OutNearestEnemy = CheackEnemy;
			PrevNearestEnemyPos = EnemyPos;
		}
	}

	return OutNearestEnemy;
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