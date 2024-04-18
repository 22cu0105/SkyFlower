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

	// 管理している敵が死亡しているか監視する
	// 死亡していたら領域を解放する
	for (ASF_EnemyBase* DestroyEnemy : TryGetDeadEnemies())
	{
		if (EnemyList.Contains(DestroyEnemy))
			EnemyList.Remove(DestroyEnemy);
	}
}

/// @brief SpawnTypeで生成方法を分ける
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

/// @brief 死亡している敵キャラクターを取得
/// @return 死亡している敵の配列
TArray<ASF_EnemyBase*> USF_EnemyManager::TryGetDeadEnemies() const
{
	// 死亡している敵のアドレス格納用
	TArray<ASF_EnemyBase*> DeadEnemyList;

	for (ASF_EnemyBase* CheackEnemy : EnemyList)
	{
		if (!IsValid(CheackEnemy)) continue;

		// 死亡しているか判定し、配列に追加
		if (CheackEnemy->IsDead())
			DeadEnemyList.Add(CheackEnemy);
	}

	return DeadEnemyList;
}

/// @brief 通常敵の生成処理
/// @param InEnemy 
/// @param InLocation 
/// @param InNum 
void USF_EnemyManager::NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// 生成数分だけ処理
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}

/// @brief 群衆敵の生成処理
/// @param InEnemy 
/// @param InLocation 
/// @param InNum 
void USF_EnemyManager::FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList;

	// 生成ロジックをここに書く

	CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// 生成数分だけ処理
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}