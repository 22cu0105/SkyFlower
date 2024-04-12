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

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void Move();
	void Attack();
	void Dead();

public:
	void SetPlayerKey(APawn* player);

};
