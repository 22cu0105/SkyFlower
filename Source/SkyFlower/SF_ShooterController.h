// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyControllerBase.h"
#include "SF_ShooterController.generated.h"

/**
 * 
 */
UCLASS()
class SKYFLOWER_API ASF_ShooterController : public ASF_EnemyControllerBase
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
