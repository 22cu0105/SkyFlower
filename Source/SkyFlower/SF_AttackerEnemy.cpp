// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_AttackerEnemy.h"
#include "DebugHelpers.h"

ASF_AttackerEnemy::ASF_AttackerEnemy()
{
}

void ASF_AttackerEnemy::GetDamage(int32 damage)
{
	hp -= damage;
	Debug::Print("EnemyMiddle GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
}

