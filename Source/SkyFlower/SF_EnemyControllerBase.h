// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 坂下 拓人
// Description: エネミーを操作する
// Update	:	2024/04/12
//				2024/04/30　State,Param
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
	Idle                UMETA(DisplayName = "なし"),
	Move				UMETA(DisplayName = "移動"),
	BeginAttack			UMETA(DisplayName = "攻撃開始時"),
	MoveAttack			UMETA(DisplayName = "移動攻撃"),
	ShortRangeAttack	UMETA(DisplayName = "近距離攻撃"),
	LongRangeAttack		UMETA(DisplayName = "遠距離攻撃"),
};

// キャラクター共通の情報をまとめた構造体
USTRUCT(BlueprintType)
struct FSF_EnemyInfo
{
	GENERATED_BODY()

public:
	// 移動速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// 近接攻撃可能距離
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackableDistance_ShortRange;
	// 遠距離攻撃可能距離
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
	// エネミーの状態
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
	ESF_EnemyState EnemyState;
	// エネミーのパラメータ情報
	UPROPERTY(EditAnywhere, Category = "Edit | Param")
	FSF_EnemyInfo EnemyParam;

public:

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetEnemyState(ESF_EnemyState InEnemyState) { EnemyState = InEnemyState; }
	UFUNCTION(BlueprintCallable, Category = "State")
	ESF_EnemyState GetEnemyState() { return EnemyState; }

public:
	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
