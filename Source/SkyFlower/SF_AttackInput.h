// ==================================================
// Filename	:	SF_CharacterBase.h
// Author	:	22cu0115 坂下拓人
// Description: 攻撃の関数定義
// Update	:	2024/04/30 22cu0214 HomingAttack実装
//				2024/04/09
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_AttackInput.generated.h"

class ASF_GameMode;
class ASF_Player;
class ASF_WeaponBase;
class ASF_EnemyBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFLOWER_API USF_AttackInput : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USF_AttackInput();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	////////////////////////////////////////// custom function
public:
	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

	void HomingShoot();
	void LockOn();

private:
	void ShortRangeAttack();
	void LongRangeAttack();

	UFUNCTION()
	void MoveToEnemy(float DeltaTime);

	void RaycastToGetTarget();

	////////////////////////////////////////// custom variable
public:
	// 自分と敵の位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector playerPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector enemyPos;
	UPROPERTY(BlueprintReadOnly)
	bool beginShortAttack = false;

	// 振り向き速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotationSpeed = 30.0f;

	// 敵を追いかける速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed = 1500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveTimeLimit = 1.5f;
	UPROPERTY(BlueprintReadOnly)
	float moveTime = 0.f;

	// 押された時間でレーザーかそれ以外か判定する
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gatherPowerTime = 3.0f;
	UPROPERTY(BlueprintReadOnly)
	float pressedTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isButtonPressed = false;

	UPROPERTY(EditDefaultsOnly)
	ASF_WeaponBase* InWeapon;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	UAnimInstance* AnimInstance;
	// 近接攻撃の距離
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackableDistance = 400.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float stoppingDistance = 100.f;

	UPROPERTY(EditAnywhere, Category = "TEST")
	TSubclassOf<AActor> MagicballClass;

	// homing attack parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 magicballNumber = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float angleStep = 360.f;

	UPROPERTY(EditAnywhere, Category = "TEST")
	TSubclassOf<AActor> HomingAttackClass;

	void NotifyActivateComboInTime();

private:
	ASF_EnemyBase* LockOnTarget = nullptr;
	bool LockOnStatus = false;

	////////////////////////////////////////// Get関数
public:
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
	ASF_EnemyBase* GetLockOnTarget() const { return LockOnTarget; }
	bool GetLockOnStatus()const { return LockOnStatus; }
};
