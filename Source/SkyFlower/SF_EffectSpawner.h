// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EffectSpawner.generated.h"

class UFXSystemAsset;

// 生成するエフェクトのタイプ
UENUM(BlueprintType)
enum class ESF_EffectType : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
	DefeatedEnemy		UMETA(DisplayName = "敵撃破時"),
};

// エフェクトのデータとパラメータを管理する構造体
USTRUCT(BlueprintType)
struct FSF_EffectInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFXSystemAsset* EffectData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Size;

public:
	FSF_EffectInfo()
		: EffectData(nullptr)
		, Size(FVector(1.f))
	{}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_EffectSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_EffectSpawner();

public:	
	// エフェクト生成処理
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void SpawnEffect(const FSF_EffectInfo& InEffectInfo, const FVector& InLocation);
};
