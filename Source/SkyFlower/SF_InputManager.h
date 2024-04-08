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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_InputManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_InputManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ���̓o�C���h����
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent);

	/********************PlayerInput********************/
	// ���_Y����]����
	void LookUp(const float InValue);
	// ���_X����]����
	void Turn(const float InValue);

	// �O�����ړ�����
	void MoveForward(const float InValue);
	// �������ړ�����
	void MoveRight(const float InValue);
	// ������ړ�����
	void MoveUp(const float InValue);

	void Attack();
};
