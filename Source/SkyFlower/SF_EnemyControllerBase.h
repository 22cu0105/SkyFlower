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
