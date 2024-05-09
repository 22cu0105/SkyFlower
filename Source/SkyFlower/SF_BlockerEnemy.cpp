#include "SF_BlockerEnemy.h"
#include "DebugHelpers.h"

ASF_BlockerEnemy::ASF_BlockerEnemy()
{
}

void ASF_BlockerEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_BlockerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASF_BlockerEnemy::GetDamage(int32 damage)
{
	hp = GetCurrentHP();
	hp -= damage;
	SetCurretnHP(hp);

	Debug::Print("BlockerEnemy GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
}
