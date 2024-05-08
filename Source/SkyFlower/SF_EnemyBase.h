// ==================================================
// Filename	:	SF_EnemyBase.h
// Author	:	22cu0115 坂下拓人
// Description: エネミーの基底クラス
// Notes:		例
//				
// Update:		2024/04/12 22cu0115 
//				2024/04/18 22cu0105 
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_EnemyBase.generated.h"

class ASF_GameMode;
class ASF_Player;

UCLASS()
class SKYFLOWER_API ASF_EnemyBase : public ASF_CharacterBase
{
	GENERATED_BODY()

public:
	ASF_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		float GetAttackCooldown() { return AttackCooldown; }
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		void SetCanAttack(const bool InCanAttack) { bCanAttack = InCanAttack; }
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
		bool GetCanAttack() { return bCanAttack; }

private:
	UPROPERTY(EditAnywhere)
		float AttackCooldown = 2.0f; // 突撃間隔
	UPROPERTY(VisibleAnywhere)
		bool bCanAttack = true;
	virtual void UpdateState(const float InDeltaTime) {};
	virtual void ChooseActionByState(const float InDeltaTime) {};

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

public:
	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
