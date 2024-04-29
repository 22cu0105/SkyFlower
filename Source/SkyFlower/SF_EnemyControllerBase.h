// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 坂下 拓人
// Description: エネミーを操作する
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
	Idle                UMETA(DisplayName = "なし"),
	Move				UMETA(DisplayName = "移動"),
	BeginAttack			UMETA(DisplayName = "攻撃開始時"),
	ShortRangeAttack	UMETA(DisplayName = "近距離攻撃"),
	LongRangeAttack		UMETA(DisplayName = "遠距離攻撃"),
};

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// エネミーの状態
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
		ESF_EnemyState EnemyState;
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		ESF_EnemyState GetEnemyState() { return EnemyState; }
	
public:
	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
