// ==================================================
// Filename	:	SF_EnemyMiddle.h
// Author	:	22cu0214 JinWener
// Description: 中型エネミー
// Notes:		
//				
// Update:		2024/04/23 22cu0214 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyBase.h"
#include "SF_EnemyMiddle.generated.h"

/**
 * 
 */
UCLASS()
class SKYFLOWER_API ASF_EnemyMiddle : public ASF_EnemyBase
{
	GENERATED_BODY()
	

public:
	// ISF_DamageableInterface を介して継承されました
	virtual void GetDamage(int32 damage) override;

private:
	int32 hp = 100;
};
