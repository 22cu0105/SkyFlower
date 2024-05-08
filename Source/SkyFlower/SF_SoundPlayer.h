// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_SoundPlayer.generated.h"

class UAudioComponent;

/************************* BGM *****************************/
// ��������BGM�̖��O
UENUM(BlueprintType)
enum class ESF_BGMType : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
};

/************************* SE *****************************/
// ��������SE�̖��O
UENUM(BlueprintType)
enum class ESF_SEType : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
};

// BGM/SE�̉����ƃp�����[�^���Ǘ�����\����
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
	// MasterVolume�ɔC�ӂ̒l��������
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMasterVolume(const float InVolume);
	// MainBGMVolume�ɔC�ӂ̒l��������
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMainBGMVolume(const float InVolume);
	// MainSEVolume�ɔC�ӂ̒l��������
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void AddMainSEVolume(const float InVolume);

	// AudioComponent����BGM���Đ�
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlayBGM(const FSF_SoundInfo& InBGMInfo);
	// SE���Đ�
	UFUNCTION(BlueprintCallable, Category = "Sound", meta = (AutoCreateRefTerm = "InVolumeMultiplier, InPitchMultiplier, InLocation"))
	void PlaySE(const FSF_SoundInfo& InSEInfo, const float InVolumeMultiplier = 1.f, const float InPitchMultiplier = 1.f, const FVector& InLocation = FVector::ZeroVector);

private:
	// BGM��pAudioComponent
	UPROPERTY(EditAnywhere)
	UAudioComponent* BGMAudioComp;

	// �ő剹��
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MaxVolume;
	// �ŏI�I�ȑS�̂̉��̑傫��
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MasterVolume;
	// �ŏI�I��BGM�̉��̑傫��
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MainBGMVolume;
	// �̎�I��SE�̉��̑傫��
	UPROPERTY(EditAnywhere, Category = "Sound | Edit")
	float MainSEVolume;

	// ���ݍĐ�����Ă���BGM�^�C�v�i�[�p
	UPROPERTY()
	FSF_SoundInfo CurrentBGMInfo;
};
