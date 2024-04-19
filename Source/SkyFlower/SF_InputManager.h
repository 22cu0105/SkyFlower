// ==================================================
// Filename	:	SF_InputManager.h
// Author	:	22cu0105 ���c�� �Ől
// Description:���͏������eActor,Character�ɑ���
// Update	:	2024/04/07
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_InputManager.generated.h"

class ASF_GameMode;
class ASF_MainCamera;
class ASF_Player;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYFLOWER_API USF_InputManager : public UActorComponent
{
	GENERATED_BODY()

public:
	USF_InputManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;


	////////////////////////////////////////// ���̓o�C���h����
public:
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent);
private:
	/********************MovementInput********************/
	// ���_Y����]����
	void LookUp(const float InValue);
	// ���_X����]����
	void Turn(const float InValue);

	// �O�����ړ�����
	void MoveForward(const float InValue);
	// �������ړ�����
	void MoveRight(const float InValue);
	// �O�����Ƀ_�b�V������
	void MoveDash();
	// ������ړ�����
	void MoveUp(const float InValue);

	/********************AttackInput********************/
	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

	////////////////////////////////////////// Get�֐�
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_MainCamera* GetMainCamera() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const; 
};
