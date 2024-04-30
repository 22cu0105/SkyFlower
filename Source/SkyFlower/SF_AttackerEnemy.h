// ==================================================
// Filename	:	SF_AttackerEnemy.h
// Author	:	22cu0115 â‰º‘ñl
// Description: AttackerEnemy‚ÌŠÇ—
// Notes:		—á
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
	// ISF_DamageableInterface ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void GetDamage(int32 damage) override;

private:
	int32 hp = 100;
	
};
