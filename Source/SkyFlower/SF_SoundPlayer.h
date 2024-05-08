// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_SoundPlayer.generated.h"

class UAudioComponent;

/************************* BGM *****************************/
// 流したいBGMの名前
UENUM(BlueprintType)
enum class ESF_BGMType : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
};

/************************* SE *****************************/
// 流したいSEの名前
UENUM(BlueprintType)
enum class ESF_SEType : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
};

// BGM/SEの音源とパラメータを管理する構造体
USTRUCT(BlueprintType)
struct FSF_SoundInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SoundData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VolumeMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PitchMultiplier;

public:
	FSF_SoundInfo()
		: SoundData(nullptr)
		, VolumeMultiplier(1.f)
		, PitchMultiplier(1.f)
	{}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_SoundPlayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_SoundPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// MasterVolumeに任意の値を加える
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMasterVolume(const float InVolume);
	// MainBGMVolumeに任意の値を加える
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMainBGMVolume(const float InVolume);
	// MainSEVolumeに任意の値を加える
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMainSEVolume(const float InVolume);

	// AudioComponentからBGMを再生
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayBGM(const FSF_SoundInfo& InBGMInfo);
	// SEを再生
	UFUNCTION(BlueprintCallable, Category = "Sound", meta = (AutoCreateRefTerm = "InVolumeMultiplier, InPitchMultiplier, InLocation"))
	void PlaySE(const FSF_SoundInfo& InSEInfo, const float InVolumeMultiplier = 1.f, const float InPitchMultiplier = 1.f, const FVector& InLocation = FVector::ZeroVector);

private:
	// BGM専用AudioComponent
	UPROPERTY(EditAnywhere)
	UAudioComponent* BGMAudioComp;

	// 最大音量
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MaxVolume;
	// 最終的な全体の音の大きさ
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MasterVolume;
	// 最終的なBGMの音の大きさ
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MainBGMVolume;
	// 採取的なSEの音の大きさ
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MainSEVolume;

	// 現在再生されているBGMタイプ格納用
	UPROPERTY()
	FSF_SoundInfo CurrentBGMInfo;
};
