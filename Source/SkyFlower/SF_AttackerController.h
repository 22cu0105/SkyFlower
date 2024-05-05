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



UCLASS()
class SKYFLOWER_API ASF_AttackerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
		float ChasePower = 5000.0f;

public:
	virtual void Normal(const float InDeltaTime) override;
	virtual void ShortRangeAttack(const float InDeltaTime) override;
	virtual void LongRangeAttack(const float InDeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "TEST")
		TSubclassOf<AActor> ProjectileClass;
};
