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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent)
		void AttackCollision(float InValue);
private:
	UPROPERTY(VisibleAnywhere)
	float TimeSinceLastAttack = 0.f;

	virtual void UpdateState(const float InDeltaTime) override;
	virtual void ChooseActionByState(const float InDeltaTime) override;

private:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;

	// ISF_DamageableInterface を介して継承されました
	virtual void GetDamage(int32 damage) override;

private:
	int32 hp = 100;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//ASF_AttackerController* SF_AttackerController;
};
