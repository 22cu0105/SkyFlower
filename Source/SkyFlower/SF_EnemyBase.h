﻿// ==================================================
// Filename	:	SF_EnemyBase.h
// Author	:	22cu0115 坂下拓人
// Description: エネミーの基底クラス
// Notes:		例
//				
// Update:		2024/04/12 22cu0115 
//				2024/04/18 22cu0105 
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_EnemyBase.generated.h"

class UPawnSensingComponent;
class UBoxComponent;

UCLASS()
class SKYFLOWER_API ASF_EnemyBase : public ASF_CharacterBase
{
	GENERATED_BODY()

public:
	ASF_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// コリジョン
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* CollisionBox;

public:
	// オーバーラップイベント
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

private:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;
};
