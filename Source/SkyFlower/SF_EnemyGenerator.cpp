#include "SF_EnemyGenerator.h"
#include "SF_EnemyBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

USF_EnemyGenerator::USF_EnemyGenerator()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USF_EnemyGenerator::BeginPlay()
{
	Super::BeginPlay();

}

void USF_EnemyGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TArray<ASF_EnemyBase*> USF_EnemyGenerator::SpawnAIEnemy(const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemyChara, UBehaviorTree* const InBehaviorTree, const int InNum)
{
	TArray<ASF_EnemyBase*> CreateEnemyList;

	// ê∂ê¨êîï™ÇæÇØèàóù
	for (int i = 0; i < InNum; i++)
		CreateEnemyList.Add(Cast<ASF_EnemyBase>(UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), InEnemyChara, InBehaviorTree, InLocation)));

	return CreateEnemyList;
}