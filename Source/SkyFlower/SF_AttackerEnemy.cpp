// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_AttackerEnemy.h"
#include "SF_AttackerController.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerEnemy::ASF_AttackerEnemy()
{
}

void ASF_AttackerEnemy::GetDamage(int32 damage)
{
	hp -= damage;
	Debug::Print("EnemyMiddle GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
	//if (ASF_AttackerController* const SF_AttackerController = Cast<ASF_AttackerController>(UGameplayStatics::GetGameMode(GetWorld())))
	//{
	//	//SF_AttackerController->Move();
	//}
}

