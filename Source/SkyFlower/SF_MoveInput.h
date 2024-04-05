// ==================================================
// Filename	:	SF_MoveInput.h
// Author	:	22cu0115 坂下拓人
// Description: 移動の関数定義
// Notes:		例
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputMappingContext.h" // 追加
#include "InputAction.h" // 追加
#include "InputActionValue.h" // 追加
#include "SF_MoveInput.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_MoveInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_MoveInput();

protected:
	// override指定子はこの関数は親クラスの関数を上書きしますという宣言みたいなもの。
	// よって↓の関数は親クラスに無いのでコンパイルエラーになっていました。
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
