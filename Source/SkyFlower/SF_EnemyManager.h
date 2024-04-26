// ==================================================
// Filename	:	SF_EnemyManager.h
// Author	:	22cu0105 小田島 稜人
// Description: 敵を生成し、管理するコンポーネント
// Update	:	2024/04/09
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EnemyManager.generated.h"

class ASF_EnemyBase;
class USF_EnemyGenerator;

// 敵の生成方法の列挙型
UENUM(BlueprintType)
enum class ESF_SpawnType : uint8
{
	None = 0		UMETA(DisplayName = "なし"),
	Normal			UMETA(DisplayName = "通常敵"),
	FlockEnemy		UMETA(DisplayName = "敵群体"),
};

//--------------------------------------------------------------------------------------------

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_EnemyManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_EnemyManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 敵の生成方法から敵AIを生成する関数を場合分けする
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	void SpawnAIEnemyFromGenerationType(const ESF_SpawnType InSpawnType, const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemy, const int InNum = 1);

	// 引数の座標に一番近い敵の座標を取得
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	ASF_EnemyBase* GetNearestEnemyPos(const FVector& InLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyManager", meta = (AllowPrivateAccess = "true"))
	USF_EnemyGenerator* EnemyGenerator;

	// 敵を管理する配列
	UPROPERTY()
	TArray<ASF_EnemyBase*> EnemyList;

public:
	// 現在生きている敵の数を取得
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	int GetCurrentEnemyNum() const { return EnemyList.Num(); }

private:
	// 管理している敵が死亡しているか判定し、死んでいたら管理領域を解放する
	TArray<ASF_EnemyBase*> TryGetDeadEnemies() const;

	void NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
	void FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
};
