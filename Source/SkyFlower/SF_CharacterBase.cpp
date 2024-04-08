#include "SF_CharacterBase.h"
#include "SF_WeaponBase.h"
#include "SF_Shield.h"

ASF_CharacterBase::ASF_CharacterBase()
	: WeaponActor(nullptr)
	, ShieldActor(nullptr)
	, CharacterState(ESF_CharacterState::None)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterState = ESF_CharacterState::Normal;
}

void ASF_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/// ToDo
/// @brief 武器を装備する
/// @param InWeapon	   キャラクターに装備させるシールド
/// @param InSoketName メッシュにアタッチさせるソケットの名前
void ASF_CharacterBase::EquipWeapon(ASF_WeaponBase* const InWeapon, const FName& InSoketName)
{
	if (!IsValid(InWeapon)) return;

	WeaponActor = InWeapon;

	// 銃アクターをプレイヤーメッシュのソケットにアタッチする
	FAttachmentTransformRules AttachTransform = { EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	WeaponActor->AttachToComponent(GetMesh(), AttachTransform, InSoketName);
}

/// ToDo
/// @brief シールドを装備する
/// @param InEquipment キャラクターに装備させるシールド
/// @param InSoketName メッシュにアタッチさせるソケットの名前
void ASF_CharacterBase::EquipShield(ASF_Shield* const InShield, const FName& InSoketName)
{
	if (!IsValid(InShield)) return;

	ShieldActor = InShield;

	// 銃アクターをプレイヤーメッシュのソケットにアタッチする
	FAttachmentTransformRules AttachTransform = { EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	ShieldActor->AttachToComponent(GetMesh(), AttachTransform, InSoketName);
}
