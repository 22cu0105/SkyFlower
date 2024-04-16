// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 �≺ ��l
//				22cu0105 ���c�� �Ől
// Description:Player���瑗���Ă�������󂯎��
// Update	:	2024/04/08
//				2024/04/16 ���c�� �q�b�g�X�g�b�v����
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

	// �q�b�g�X�g�b�v�J�n
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
	// �q�b�g�X�g�b�v����
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	bool bIsInHitStop;
	// �q�b�g�X�g�b�v�̑��x
	UPROPERTY(EditAnywhere, Category = "HitStop | Edit")
	float HitStopSpeed;
	// �q�b�g�X�g�b�v�̎���
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float HitStopTime;
	// �q�b�g�X�g�b�v�^�C�}�[�p
	UPROPERTY(VisibleInstanceOnly, Category = "HitStop | Visible")
	float Timer_HitStop;
};
