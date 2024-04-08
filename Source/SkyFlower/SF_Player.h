// ==================================================
// Filename	:	SF_Player.h
// Author	:	22cu0115 ç‚â∫ ëÒêl
// Description:
// Update	:	2024/04/08
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_Player.generated.h"

class USF_MoveInput;
class USF_AttackInput;

UCLASS()
class SKYFLOWER_API ASF_Player : public ASF_CharacterBase
{
	GENERATED_BODY()

public:
	ASF_Player();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveForward(const float InValue);
	void MoveRight(const float InValue);
	void MoveUp(const float InValue);

	void Attack();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USF_MoveInput* MoveInputComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USF_AttackInput* AttackInputComponent;
};