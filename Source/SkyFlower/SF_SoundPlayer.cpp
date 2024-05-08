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

	// コンポーネント生成
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

/// @brief ゲーム全体の音量を上げる処理
/// @param InVolume 
void USF_SoundPlayer::AddMasterVolume(const float InVolume)
{
	MasterVolume += InVolume;

	// 補正
	if (MasterVolume > MaxVolume)
		MasterVolume = MaxVolume;
	else if (MasterVolume < 0.f)
		MasterVolume = 0.f;

	// BGMが再生されている場合、変更した音量をセットする
	if (IsValid(CurrentBGMInfo.SoundData))
		BGMAudioComp->SetVolumeMultiplier(CurrentBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
}

/// @brief BGM全体の音量を上げる処理
/// @param InVolume 
void USF_SoundPlayer::AddMainBGMVolume(const float InVolume)
{
	MainBGMVolume += InVolume;

	// 補正
	if (MainBGMVolume > MaxVolume)
		MainBGMVolume = MaxVolume;
	else if (MainBGMVolume < 0.f)
		MainBGMVolume = 0.f;

	// BGMが再生されている場合、変更した音量をセットする
	if (IsValid(CurrentBGMInfo.SoundData))
		BGMAudioComp->SetVolumeMultiplier(CurrentBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
}

/// @brief SE全体の音量を上げる処理
/// @param InVolume 
void USF_SoundPlayer::AddMainSEVolume(const float InVolume)
{
	MainSEVolume += InVolume;
	// 補正
	if (MainSEVolume > MaxVolume)
		MainSEVolume = MaxVolume;
	else if (MainSEVolume < 0.f)
		MainSEVolume = 0.f;
}

/// @brief BGM再生処理
/// @param InBGMInfo 再生するBGMの情報
void USF_SoundPlayer::PlayBGM(const FSF_SoundInfo& InBGMInfo)
{
	if (!IsValid(InBGMInfo.SoundData)) return;

	// 再生したいBGMのタイプを格納・初期化し再生
	CurrentBGMInfo = InBGMInfo;
	BGMAudioComp->SetSound(InBGMInfo.SoundData);
	BGMAudioComp->SetVolumeMultiplier(InBGMInfo.VolumeMultiplier * MasterVolume * MainBGMVolume);
	BGMAudioComp->Play(0.f);
}

/// @brief SE再生処理
/// @param InSEInfo			  再生したいSEの情報
/// @param InVolumeMultiplier 音量
/// @param InPitchMultiplier  ピッチ
/// @param InLocation		  3D音源を再生したい座標
void USF_SoundPlayer::PlaySE(const FSF_SoundInfo& InSEInfo, const float InVolumeMultiplier, const float InPitchMultiplier, const FVector& InLocation)
{
	if (!IsValid(InSEInfo.SoundData)) return;

	// 3D音源再生処理
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
	// 2D音源再生処理
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