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

	// ŠÇ—‚µ‚Ä‚¢‚é“G‚ª€–S‚µ‚Ä‚¢‚é‚©ŠÄ‹‚·‚é
	// €–S‚µ‚Ä‚¢‚½‚ç—Ìˆæ‚ğ‰ğ•ú‚·‚é
	for (ASF_EnemyBase* DestroyEnemy : TryGetDeadEnemies())
	{
		if (EnemyList.Contains(DestroyEnemy))
			EnemyList.Remove(DestroyEnemy);
	}
}
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

TArray<ASF_EnemyBase*> USF_EnemyManager::TryGetDeadEnemies() const
{
	// €–S‚µ‚Ä‚¢‚é“G‚ÌƒAƒhƒŒƒXŠi”[—p
	TArray<ASF_EnemyBase*> DeadEnemyList;

	//for (ASF_EnemyBase* CheackEnemy : EnemyList)
	//{
	//	if (!IsValid(CheackEnemy)) continue;

	//	// €–S‚µ‚Ä‚¢‚é‚©”»’è‚µA”z—ñ‚É’Ç‰Á
	//	if (CheackEnemy->GetCharacterState() == EBO_CharacterState::Dead)
	//		DeadEnemyList.Add(CheackEnemy);
	//}

	return DeadEnemyList;
}

void USF_EnemyManager::NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// ¶¬”•ª‚¾‚¯ˆ—
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}

void USF_EnemyManager::FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum)
{
	if (!IsValid(EnemyGenerator)) return;

	TArray<ASF_EnemyBase*> CreateEnemyList;

	// ¶¬ƒƒWƒbƒN‚ğ‚±‚±‚É‘‚­

	CreateEnemyList = EnemyGenerator->SpawnAIEnemy(InLocation, InEnemy, nullptr, InNum);

	// ¶¬”•ª‚¾‚¯ˆ—
	for (ASF_EnemyBase* CreateEnemy : CreateEnemyList)
	{
		if (IsValid(CreateEnemy))
			EnemyList.Add(CreateEnemy);
	}
}