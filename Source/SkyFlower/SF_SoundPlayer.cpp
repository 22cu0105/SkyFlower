#include "SF_SoundPlayer.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

USF_SoundPlayer::USF_SoundPlayer()
	: MaxVolume(3.f)
	, MasterVolume(1.f)
	, MainBGMVolume(1.f)
	, MainSEVolume(1.f)
{
	PrimaryComponentTick.bCanEverTick = false;

	// �R���|�[�l���g����
	BGMAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMAudioPlayer"));
}

void USF_SoundPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void USF_SoundPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

/// @brief �Q�[���S�̂̉��ʂ��グ�鏈��
/// @param InVolume 
void USF_SoundPlayer::AddMasterVolume(const float InVolume)
{
	MasterVolume += InVolume;

	// �␳
	if (MasterVolume > MaxVolume)
		MasterVolume = MaxVolume;
	else if (MasterVolume < 0.f)
		MasterVolume = 0.f;

	// BGM���Đ�����Ă���ꍇ�A�ύX�������ʂ��Z�b�g����
	if (IsValid(CurrentBGMInfo.SoundData))
		BGMAudioComp->SetVolumeMultiplier(CurrentBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
}

/// @brief BGM�S�̂̉��ʂ��グ�鏈��
/// @param InVolume 
void USF_SoundPlayer::AddMainBGMVolume(const float InVolume)
{
	MainBGMVolume += InVolume;

	// �␳
	if (MainBGMVolume > MaxVolume)
		MainBGMVolume = MaxVolume;
	else if (MainBGMVolume < 0.f)
		MainBGMVolume = 0.f;

	// BGM���Đ�����Ă���ꍇ�A�ύX�������ʂ��Z�b�g����
	if (IsValid(CurrentBGMInfo.SoundData))
		BGMAudioComp->SetVolumeMultiplier(CurrentBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
}

/// @brief SE�S�̂̉��ʂ��グ�鏈��
/// @param InVolume 
void USF_SoundPlayer::AddMainSEVolume(const float InVolume)
{
	MainSEVolume += InVolume;
	// �␳
	if (MainSEVolume > MaxVolume)
		MainSEVolume = MaxVolume;
	else if (MainSEVolume < 0.f)
		MainSEVolume = 0.f;
}

/// @brief BGM�Đ�����
/// @param InBGMInfo �Đ�����BGM�̏��
void USF_SoundPlayer::PlayBGM(const FSF_SoundInfo& InBGMInfo)
{
	if (!IsValid(InBGMInfo.SoundData)) return;

	// �Đ�������BGM�̃^�C�v���i�[�E���������Đ�
	CurrentBGMInfo = InBGMInfo;
	BGMAudioComp->SetSound(InBGMInfo.SoundData);
	BGMAudioComp->SetVolumeMultiplier(InBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
	BGMAudioComp->Play(0.f);
}

/// @brief SE�Đ�����
/// @param InSEInfo			  �Đ�������SE�̏��
/// @param InVolumeMultiplier ����
/// @param InPitchMultiplier  �s�b�`
/// @param InLocation		  3D�������Đ����������W
void USF_SoundPlayer::PlaySE(const FSF_SoundInfo& InSEInfo, const float InVolumeMultiplier, const float InPitchMultiplier, const FVector& InLocation)
{
	if (!IsValid(InSEInfo.SoundData)) return;

	// 3D�����Đ�����
	if (InLocation != FVector::ZeroVector)
	{
		UGameplayStatics::PlaySoundAtLocation(
			/*WorldContext	   = */GetWorld(),
			/*Sound			   = */InSEInfo.SoundData,
			/*Location		   = */InLocation,
			/*Rotation		   = */FRotator::ZeroRotator,
			/*VolumeMultiplier = */InSEInfo.VolumeMultiplier * InVolumeMultiplier * MasterVolume * MainSEVolume,
			/*PitchMultiplier  = */InSEInfo.PitchMultiplier * InPitchMultiplier,
			/*StartTime		   = */0.0f);
	}
	// 2D�����Đ�����
	else
	{
		UGameplayStatics::PlaySound2D(
			/*WorldContext	   = */GetWorld(),
			/*Sound			   = */InSEInfo.SoundData,
			/*VolumeMultiplier = */InSEInfo.VolumeMultiplier * InVolumeMultiplier * MasterVolume * MainSEVolume,
			/*PitchMultiplier  = */InSEInfo.PitchMultiplier * InPitchMultiplier,
			/*StartTime		   = */0.0f);
	}
}