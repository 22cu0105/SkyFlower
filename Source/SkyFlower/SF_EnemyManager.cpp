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

	// 事前にマップ上に敵が配置されている敵を検索し、格納
	// デバッグ用。実際は事前にマップ上に敵がいることは決してない
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

/// @brief 引数で渡された座標に一番近い敵の座標を取得
/// @param InLocation 比較する座標
/// @return 
ASF_EnemyBase* USF_EnemyManager::GetNearestEnemyPos(const FVector& playerLocation)
{
	//init
	ASF_EnemyBase* OutNearestEnemy = nullptr;
	float PrevLength = playerLocation.Size();

	//find target in EnemyList
	for (ASF_EnemyBase* CheackEnemy : EnemyList)
	{
		//if null return
		if (!IsValid(CheackEnemy)) continue;

		//get distance for this enemy
		const FVector EnemyPos = CheackEnemy->GetActorLocation();
		const float CurrentLength = (EnemyPos - playerLocation).Size();

		if (CurrentLength < PrevLength)
		{
			OutNearestEnemy = CheackEnemy;
			PrevLength = CurrentLength;
		}
	}

	return OutNearestEnemy;
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