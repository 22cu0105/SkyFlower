// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyBase.h"
#include "SF_AttackerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SKYFLOWER_API ASF_AttackerEnemy : public ASF_EnemyBase
{
	GENERATED_BODY()
public:
	ASF_AttackerEnemy();
public:
	// ISF_DamageableInterface ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void GetDamage(int32 damage) override;

private:
	int32 hp = 100;
	
};
