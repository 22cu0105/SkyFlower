// ==================================================
// Filename	:	SF_InputManager.h
// Author	:	22cu0105 ���c�� �Ől
// Description:
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
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	/********************PlayerInput********************/
	// ���_Y����]����
	UFUNCTION()
	void LookUp(const float InValue);
	// ���_X����]����
	UFUNCTION()
	void Turn(const float InValue);

	// �O�����ړ�����
	UFUNCTION()
	void MoveForward(const float InValue);
	// �������ړ�����
	UFUNCTION()
	void MoveRight(const float InValue);
};
