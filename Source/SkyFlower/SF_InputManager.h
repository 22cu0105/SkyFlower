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


	////////////////////////////////////////// 入力バインド処理
public:
	UFUNCTION()
	void SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent);
private:
	/********************MovementInput********************/
	// 視点Y軸回転処理
	void LookUp(const float InValue);
	// 視点X軸回転処理
	void Turn(const float InValue);

	// 前方向移動処理
	void MoveForward(const float InValue);
	// 横方向移動処理
	void MoveRight(const float InValue);
	// 前方向にダッシュする
	void MoveDash();
	// 上方向移動処理
	void MoveUp(const float InValue);

	/********************AttackInput********************/
	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_MainCamera* GetMainCamera() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const; 
};
