#include "SF_BattleData.h"

USF_BattleData::USF_BattleData()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USF_BattleData::BeginPlay()
{
	Super::BeginPlay();

}

void USF_BattleData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

