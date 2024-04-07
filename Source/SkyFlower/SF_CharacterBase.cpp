#include "SF_CharacterBase.h"
#include "SF_WeaponBase.h"
#include "SF_Shield.h"

ASF_CharacterBase::ASF_CharacterBase()
	: WeaponActor(nullptr)
	, ShieldActor(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASF_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASF_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// ToDo
/// @brief ����𑕔�����
/// @param InWeapon	   �L�����N�^�[�ɑ���������V�[���h
/// @param InSoketName ���b�V���ɃA�^�b�`������\�P�b�g�̖��O
void ASF_CharacterBase::EquipWeapon(ASF_WeaponBase* const InWeapon, const FName& InSoketName)
{
	if (!IsValid(InWeapon)) return;

	WeaponActor = InWeapon;

	// �e�A�N�^�[���v���C���[���b�V���̃\�P�b�g�ɃA�^�b�`����
	FAttachmentTransformRules AttachTransform = { EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	WeaponActor->AttachToComponent(GetMesh(), AttachTransform, InSoketName);
}

/// ToDo
/// @brief �V�[���h�𑕔�����
/// @param InEquipment �L�����N�^�[�ɑ���������V�[���h
/// @param InSoketName ���b�V���ɃA�^�b�`������\�P�b�g�̖��O
void ASF_CharacterBase::EquipShield(ASF_Shield* const InShield, const FName& InSoketName)
{
	if (!IsValid(InShield)) return;

	ShieldActor = InShield;

	// �e�A�N�^�[���v���C���[���b�V���̃\�P�b�g�ɃA�^�b�`����
	FAttachmentTransformRules AttachTransform = { EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	ShieldActor->AttachToComponent(GetMesh(), AttachTransform, InSoketName);
}