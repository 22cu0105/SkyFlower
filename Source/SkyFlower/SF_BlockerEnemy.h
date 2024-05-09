// ==================================================
// Filename	:	SF_BlockerEnemy.h
// Author	:	22cu0115 �≺��l
// Description: �v���C���[�̐i�s���ז����Ă���G�̊Ǘ�
// Notes:		��
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyBase.h"
#include "SF_BlockerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SKYFLOWER_API ASF_BlockerEnemy : public ASF_EnemyBase
{
	GENERATED_BODY()
public:
	ASF_BlockerEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// ISF_DamageableInterface ����Čp������܂���
	virtual void GetDamage(int32 damage) override;

private:
	UPROPERTY(VisibleAnywhere)
		float TimeSinceLastAttack = 0.f;
private:
	int32 hp = 100;

};
