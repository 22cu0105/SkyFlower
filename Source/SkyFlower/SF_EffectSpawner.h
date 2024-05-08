// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EffectSpawner.generated.h"

class UFXSystemAsset;

// ��������G�t�F�N�g�̃^�C�v
UENUM(BlueprintType)
enum class ESF_EffectType : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	DefeatedEnemy		UMETA(DisplayName = "�G���j��"),
};

// �G�t�F�N�g�̃f�[�^�ƃp�����[�^���Ǘ�����\����
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
	// �G�t�F�N�g��������
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void SpawnEffect(const FSF_EffectInfo& InEffectInfo, const FVector& InLocation);
};
