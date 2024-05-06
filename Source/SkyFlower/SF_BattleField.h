#pragma once

#include "CoreMinimal.h"
#include "SF_FieldBase.h"
#include "SF_BattleField.generated.h"

struct FSF_BattleStageInfo;

UCLASS()
class SKYFLOWER_API ASF_BattleField : public ASF_FieldBase
{
	GENERATED_BODY()
	
public:
	ASF_BattleField();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "BattleField")
	uint8 StageID;

	UPROPERTY()
	FSF_BattleStageInfo BattleStageInfo;
	UPROPERTY()
	TArray<ASF_EnemyBase*> StageEnemyList;
	UPROPERTY()
	int CurrentWaveCnt;

private:
	FSF_BattleStageInfo GetBattleStageData() const;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnPlayerEnterBattleField();

	void UpdateOnActive(const float InDeltaTime);
	void SpawnAllEnemiesInWave(const int InWaveCnt);
};