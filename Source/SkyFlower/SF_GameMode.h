// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 坂下 拓人
//				22cu0105 小田島 稜人
// Description:Playerから送られてくる情報を受け取る
// Update	:	2024/04/08
//				2024/04/16 小田島 ヒットストップ処理
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SF_GameMode.generated.h"

class USF_InputManager;
class ASF_Player;
class ASF_MainCamera;

UCLASS()
class SKYFLOWER_API ASF_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASF_GameMode();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent);

	// ヒットストップ開始
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void StartHitStop(const float InHitStopSpeed, const float InHitStopTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	USF_InputManager* InputManager;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	ASF_Player* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	ASF_MainCamera* MainCamera;


public:
	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	void SetPlayerCharacter(ASF_Player* const InPlayerCharacter) { PlayerCharacter = InPlayerCharacter; }

	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	void SetMainCamera(ASF_MainCamera* const InMainCamera) { MainCamera = InMainCamera; }

	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	ASF_Player* GetPlayerCharacter() const { return PlayerCharacter; }

	UFUNCTION(BlueprintCallable, Category = "SF_GameMode")
	ASF_MainCamera* GetMainCamera() const { return MainCamera; }

private:
	// ヒットストップ中か
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	bool bIsInHitStop;
	// ヒットストップの速度
	UPROPERTY(EditAnywhere, Category = "HitStop | Edit")
	float HitStopSpeed;
	// ヒットストップの時間
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float HitStopTime;
	// ヒットストップタイマー用
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float Timer_HitStop;
};
