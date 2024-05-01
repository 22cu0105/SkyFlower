// ==================================================
// Filename	:	SF_AttackerEnemy.h
// Author	:	22cu0115 坂下拓人
// Description: AttackerEnemyの管理
// Notes:		例
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyBase.h"
#include "SF_AttackerEnemy.generated.h"

UCLASS()
class SKYFLOWER_API ASF_AttackerEnemy : public ASF_EnemyBase
{
	GENERATED_BODY()
public:
	ASF_AttackerEnemy();
public:
	// ISF_DamageableInterface を介して継承されました
	virtual void GetDamage(int32 damage) override;

private:
	int32 hp = 100;
	
};
