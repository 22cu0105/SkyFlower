#include "SF_EnemyMiddle.h"
#include "SF_AttackerController.h"
#include "DebugHelpers.h"

ASF_EnemyMiddle::ASF_EnemyMiddle()
{
	// Create and attach AIController
	AIControllerClass = ASF_AttackerController::StaticClass();
}

void ASF_EnemyMiddle::GetDamage(int32 damage)
{
	hp -= damage;
	Debug::Print("EnemyMiddle GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
}