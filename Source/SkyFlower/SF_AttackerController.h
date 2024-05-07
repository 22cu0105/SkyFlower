// ==================================================
// Filename	:	SF_AttackerController.h
// Author	:	22cu0115 坂下拓人
// Description: 主人公に突貫してくる敵
// Notes:		例
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyControllerBase.h"
#include "SF_AttackerController.generated.h"

class ASF_AttackerEnemy;

UCLASS()
class SKYFLOWER_API ASF_AttackerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()
public:
	ASF_AttackerController();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	float ChasePower = 5000.0f;

public:
	virtual void Normal(const float InDeltaTime) override;
	virtual void ShortRangeAttack(const float InDeltaTime) override;
	virtual void LongRangeAttack(const float InDeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	float TimeSinceLastAttack = 0.f;

	virtual void UpdateState(const float InDeltaTime) override;
	virtual void ChooseActionByState(const float InDeltaTime) override;

private:
	virtual void UpdateOnNormal(const float InDeltaTime) override;
	virtual void OnBeginAttack() override;
	virtual void UpdateOnShortRangeAttack(const float InDeltaTime) override;
	virtual void UpdateOnLongRangeAttack(const float InDeltaTime) override;
	virtual void OnEndAttack() override;
	virtual void OnBeginDead() override;
	virtual void UpdateOnDead(const float InDeltaTime) override;
	virtual void OnEndDead() override;

	UPROPERTY(EditAnywhere, Category = "TEST")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ASF_AttackerEnemy* SF_AttackerEnemy;
};
