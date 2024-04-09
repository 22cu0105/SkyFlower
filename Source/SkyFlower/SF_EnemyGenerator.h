// ==================================================
// Filename	:	SF_EnemyGenerator.h
// Author	:	22cu0105 ���c�� �Ől
// Description: �G�̐����������s���R���|�[�l���g
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

	// �GAI�𐶐����鏈��
	UFUNCTION(BlueprintCallable, Category = "EnemyGenerator")
	TArray<ASF_EnemyBase*> SpawnAIEnemy(const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemyChara, UBehaviorTree* const InBehaviorTree = nullptr, const int InNum = 1);
};
