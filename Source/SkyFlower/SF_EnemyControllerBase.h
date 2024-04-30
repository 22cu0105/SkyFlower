// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 �≺ ��l
// Description: �G�l�~�[�𑀍삷��
// Update	:	2024/04/12
//				2024/04/30�@State,Param
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
	MoveAttack			UMETA(DisplayName = "�ړ��U��"),
	ShortRangeAttack	UMETA(DisplayName = "�ߋ����U��"),
	LongRangeAttack		UMETA(DisplayName = "�������U��"),
};

// �L�����N�^�[���ʂ̏����܂Ƃ߂��\����
USTRUCT(BlueprintType)
struct FSF_EnemyInfo
{
	GENERATED_BODY()

public:
	// �ړ����x
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// �ߐڍU���\����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_ShortRange;
	// �������U���\����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_LongRange;

public:
	FSF_EnemyInfo()
		: MoveSpeed(600.f)
		, AttackableDistance_ShortRange(500.f)
		, AttackableDistance_LongRange(2000.f)
	{}
};

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	// �G�l�~�[�̏��
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
	ESF_EnemyState EnemyState;
	// �G�l�~�[�̃p�����[�^���
	UPROPERTY(EditAnywhere, Category = "Edit | Param")
	FSF_EnemyInfo EnemyParam;

public:

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetEnemyState(ESF_EnemyState InEnemyState) { EnemyState = InEnemyState; }
	UFUNCTION(BlueprintCallable, Category = "State")
	ESF_EnemyState GetEnemyState() { return EnemyState; }

public:
	////////////////////////////////////////// Get�֐�
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
