#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_BattleData.generated.h"

class ASF_EnemyBase;

/// @brief MapでMapを管理するための構造体
//USTRUCT(BlueprintType)
//struct FSF_BattleEnemyInfo
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	uint8 GenerateCnt;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	TMap<ASF_EnemyBase*, FSF_ChangeValueInfo> InfoMap;
//
//public:
//	FSF_BattleEnemyInfo()
//		: CurrentMode(ESF_AddValueMode::None)
//		, InfoMap()
//	{}
//};
//
///// @brief MapでMapを管理するための構造体
//USTRUCT(BlueprintType)
//struct FSF_BattleInfo
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	ESF_AddValueMode CurrentMode;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	TMap<ASF_EnemyBase*, FSF_ChangeValueInfo> InfoMap;
//
//public:
//	FSF_BattleInfo()
//		: CurrentMode(ESF_AddValueMode::None)
//		, InfoMap()
//	{}
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_BattleData : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_BattleData();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
