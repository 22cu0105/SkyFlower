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
#include "SF_Player.h"
#include "SF_EnemyControllerBase.generated.h"

class ASF_GameMode;
class ASF_Player;

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()

private:
	// 敵の位置とプレイヤーの位置を取得し、方向ベクトルを計算
	//UPROPERTY(VisibleAnywhere)
	//FVector Direction;

public:
	//FVector GetPlayerDirection() { return GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation().GetSafeNormal();; }

public:
	virtual void Normal(const float InDeltaTime) {};
	virtual void ShortRangeAttack(const float InDeltaTime) {};
	virtual void LongRangeAttack(const float InDeltaTime) {};

public:
	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
