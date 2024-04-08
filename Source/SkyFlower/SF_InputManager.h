// ==================================================
// Filename	:	SF_InputManager.h
// Author	:	22cu0105 小田島 稜人
// Description:入力処理を各Actor,Characterに送る
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

	// 入力バインド処理
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent);

	/********************PlayerInput********************/
	// 視点Y軸回転処理
	void LookUp(const float InValue);
	// 視点X軸回転処理
	void Turn(const float InValue);

	// 前方向移動処理
	void MoveForward(const float InValue);
	// 横方向移動処理
	void MoveRight(const float InValue);
	// 上方向移動処理
	void MoveUp(const float InValue);

	void Attack();
};
