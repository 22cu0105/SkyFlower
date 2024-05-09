#pragma once

#include "CoreMinimal.h"
#include "SF_FieldBase.h"
#include "SF_StageInfo.h"
#include "SF_BattleField.generated.h"

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
	FSF_StageInfo BattleStageInfo;
	UPROPERTY()
	TArray<ASF_EnemyBase*> StageEnemyList;
	UPROPERTY()
	int CurrentWaveCnt;

private:
	FSF_StageInfo GetBattleStageData(const uint8 InStageID) const;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnPlayerEnterBattleField();

	void UpdateOnActive(const float InDeltaTime);
	void SpawnAllEnemiesInWave(const int InWaveCnt);
};