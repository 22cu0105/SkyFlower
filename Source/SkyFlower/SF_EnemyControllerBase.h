// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 �≺ ��l
// Description: �G�l�~�[�𑀍삷��
// Update	:	2024/04/12
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SF_EnemyControllerBase.generated.h"

class ASF_GameMode;
class ASF_Player;

UENUM(BlueprintType)
enum class ESF_EnemyState : uint8
{
	Idle                UMETA(DisplayName = "�Ȃ�"),
	Move				UMETA(DisplayName = "�ړ�"),
	BeginAttack			UMETA(DisplayName = "�U���J�n��"),
	ShortRangeAttack	UMETA(DisplayName = "�ߋ����U��"),
	LongRangeAttack		UMETA(DisplayName = "�������U��"),
};

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// �G�l�~�[�̏��
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
		ESF_EnemyState EnemyState;
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		ESF_EnemyState GetEnemyState() { return EnemyState; }
	
public:
	////////////////////////////////////////// Get�֐�
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
