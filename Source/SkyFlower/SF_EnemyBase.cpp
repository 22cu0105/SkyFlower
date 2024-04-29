#include "SF_EnemyBase.h"
#include "SF_Player.h"
#include "SF_EnemyControllerBase.h"
#include "DebugHelpers.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASF_EnemyBase::ASF_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead())
		if (GetCurrentHP() <= 0.f)
			SetCharacterState(ESF_CharacterState::BeginDead);
	
	switch (GetCharacterState())
	{
	case ESF_CharacterState::Normal:
		UpdateOnNormal(DeltaTime);
		break;
	case ESF_CharacterState::BeginDead:
		OnBeginDead();
		break;
	case ESF_CharacterState::Dead:
		UpdateOnDead(DeltaTime);
		break;
	case ESF_CharacterState::EndDead:
		OnEndDead();
		break;
	}
}

/// ToDo
/// @brief �ʏ펞�X�V����
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnNormal(const float InDeltaTime)
{

}

/// ToDo
/// @brief �U���J�n������
void ASF_EnemyBase::OnBeginAttack()
{
}

/// ToDo
/// @brief �ߐڍU���X�V����
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnShortRangeAttack(const float InDeltaTime)
{
}

/// ToDo
/// @brief �������U���X�V����
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnLongRangeAttack(const float InDeltaTime)
{

}

/// @brief �U���I��������
void ASF_EnemyBase::OnEndAttack()
{
}

/// ToDo
/// @brief ���S�J�n��������
void ASF_EnemyBase::OnBeginDead()
{
	SetCharacterState(ESF_CharacterState::Dead);
}

/// ToDo
/// @brief ���S���X�V����
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnDead(const float InDeltaTime)
{
	SetCharacterState(ESF_CharacterState::EndDead);
}

/// @brief ���S�I��������
void ASF_EnemyBase::OnEndDead()
{
	Destroy();
}

void ASF_EnemyBase::GetDamage(int32 damage)
{
	Debug::PrintFixedLine("GetDamage EnemyBase");
}
