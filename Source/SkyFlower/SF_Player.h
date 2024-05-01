// ==================================================
// Filename	:	SF_Player.h
// Author	:	22cu0115 坂下 拓人
// Description:
// Update	:	2024/04/08
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_Player.generated.h"

class USF_MoveInput;
class USF_AttackInput;
class ASF_EnemyBase;

UCLASS()
class SKYFLOWER_API ASF_Player : public ASF_CharacterBase
{
	GENERATED_BODY()

public:
	ASF_Player();

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveForward(const float InValue);
	void MoveRight(const float InValue);
	void MoveUp(const float InValue);
	void MoveDash();

	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USF_MoveInput* MoveInputComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USF_AttackInput* AttackInputComponent;

private:
	// ISF_DamageableInterface を介して継承されました
	virtual void GetDamage(int32 damage) override;
	/// @brief プレイヤーの状態を常に変更
	void UpdateSetPlayerState();
};