// ==================================================
// Filename	:	SF_FlockerController.h
// Author	:	22cu0115 坂下拓人
// Description: 群集エネミー
// Notes:		例
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyControllerBase.h"
#include "SF_FlockerController.generated.h"

UCLASS()
class SKYFLOWER_API ASF_FlockerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()
	
public:
	ASF_FlockerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
