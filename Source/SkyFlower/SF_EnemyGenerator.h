// ==================================================
// Filename	:	SF_EnemyGenerator.h
// Author	:	22cu0105 小田島 稜人
// Description: 敵の生成処理を行うコンポーネント
// Update	:	2024/04/09
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EnemyGenerator.generated.h"

class ASF_EnemyBase;
class UBehaviorTree;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_EnemyGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_EnemyGenerator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 敵AIを生成する処理
	UFUNCTION(BlueprintCallable, Category = "EnemyGenerator")
	TArray<ASF_EnemyBase*> SpawnAIEnemy(const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemyChara, UBehaviorTree* const InBehaviorTree = nullptr, const int InNum = 1);
};
