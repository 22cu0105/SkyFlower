// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 坂下 拓人
// Description: エネミーを操作する
// Update	:	2024/04/12
//				2024/04/30　State,Param
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SF_Player.h"
#include "SF_EnemyControllerBase.generated.h"

class ASF_GameMode;
class ASF_Player;

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

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
	virtual void UpdateOnNormal(const float InDeltaTime) {};
	virtual void OnBeginAttack() {};
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) {};
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) {};
	virtual void OnEndAttack() {};
	virtual void OnBeginDead() {};
	virtual void UpdateOnDead(const float InDeltaTime) {};
	virtual void OnEndDead() {};

public:
	virtual void Normal(const float InDeltaTime) {};
	virtual void ShortRangeAttack(const float InDeltaTime) {};
	virtual void LongRangeAttack(const float InDeltaTime) {};

public:
	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
