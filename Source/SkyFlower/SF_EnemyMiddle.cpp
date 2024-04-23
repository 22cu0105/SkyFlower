// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_EnemyMiddle.h"
#include "DebugHelpers.h"

void ASF_EnemyMiddle::GetDamage(int32 damage)
{
	hp -= damage;
	Debug::Print("EnemyMiddle GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
}
