// ==================================================
// Filename	:	SF_MoveInput.h
// Author	:	22cu0115 �≺��l
// Description: �ړ��̊֐���`
// Notes:		��
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputMappingContext.h" // �ǉ�
#include "InputAction.h" // �ǉ�
#include "InputActionValue.h" // �ǉ�
#include "SF_MoveInput.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_MoveInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_MoveInput();

protected:
	// override�w��q�͂��̊֐��͐e�N���X�̊֐����㏑�����܂��Ƃ����錾�݂����Ȃ��́B
	// ����ā��̊֐��͐e�N���X�ɖ����̂ŃR���p�C���G���[�ɂȂ��Ă��܂����B
	void SetupPlayerInputComponent(UEnhancedInputComponent* const EnhancedInputComponent);
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

private:
	/** Action Input */
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MoveAction;

	/** Axis Input */
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* JumpAction;
};
