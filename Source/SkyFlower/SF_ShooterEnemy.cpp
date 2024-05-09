#include "SF_ShooterEnemy.h"
#include "SF_ShooterController.h"
#include "DebugHelpers.h"

ASF_ShooterEnemy::ASF_ShooterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_ShooterEnemy::BeginPlay()
{
    Super::BeginPlay();

    //// �G�̎��ۂ̍s��
    //SF_ShooterController = Cast<ASF_ShooterController>(GetOwner());
}

void ASF_ShooterEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //UpdateState(DeltaTime);
    //ChooseActionByState(DeltaTime);
}

/// <summary>
/// �X�e�[�g���X�V����֐� 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterEnemy::UpdateState(const float InDeltaTime)
{
    //if (!IsValid(SF_ShooterController)) return;
    if (GetCharacterState() != ESF_CharacterState::Normal)return;

    // �v���C���[�Ǝ����̒����������v�Z
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetActorLocation());

    // �X�e�[�g���f
    if (dis <= GetAttackableDistance_ShortRange() && GetCanAttack())
    {
        SetCharacterState(ESF_CharacterState::ShortRangeAttack);
    }
    else if (dis <= GetAttackableDistance_LongRange() && GetCanAttack())
    {
        SetCharacterState(ESF_CharacterState::LongRangeAttack);
    }

}

/// <summary>
/// ���݂̃X�e�[�g����s��������
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterEnemy::ChooseActionByState(const float InDeltaTime)
{
    //if (!IsValid(SF_ShooterController)) return;

    switch (GetCharacterState()) {
    case ESF_CharacterState::Normal:
    {
        UpdateOnNormal(InDeltaTime);
        break;
    }
    case ESF_CharacterState::BeginAttack:
    {
        SetCharacterState(ESF_CharacterState::Normal);
        break;
    }
    case ESF_CharacterState::ShortRangeAttack:
    {
        UpdateOnShortRangeAttack(InDeltaTime);
        break;
    }
    case ESF_CharacterState::LongRangeAttack:
    {
        UpdateOnLongRangeAttack(InDeltaTime);
        break;
    }
    default:
    {
        break;
    }
    }
}

void ASF_ShooterEnemy::UpdateOnNormal(const float InDeltaTime)
{
    //SF_ShooterController->Normal(InDeltaTime);

    TimeSinceLastAttack += InDeltaTime;

    // �U��������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
    if (TimeSinceLastAttack >= GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // ���Z�b�g
    }
}

void ASF_ShooterEnemy::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_ShooterEnemy::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    //SF_ShooterController->ShortRangeAttack(InDeltaTime);
   
    // �v���C���[�Ǝ����̒����������v�Z
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetActorLocation());

    // �X�e�[�g���f
    if (dis <= GetAttackableDistance_LongRange() && GetCanAttack())
    {
        OnEndAttack();
    }
}

void ASF_ShooterEnemy::UpdateOnLongRangeAttack(const float InDeltaTime)
{
    //SF_ShooterController->LongRangeAttack(InDeltaTime);
    OnEndAttack();
}

void ASF_ShooterEnemy::OnEndAttack()
{
    SetCanAttack(false);
    SetCharacterState(ESF_CharacterState::Normal);
}

void ASF_ShooterEnemy::OnBeginDead()
{
}

void ASF_ShooterEnemy::UpdateOnDead(const float InDeltaTime)
{
}

void ASF_ShooterEnemy::OnEndDead()
{
}

void ASF_ShooterEnemy::GetDamage(int32 damage)
{
    hp = GetCurrentHP();
    hp -= damage;
    SetCurretnHP(hp);

    Debug::Print("ShooterEnemy GetDamage : " + FString::FromInt(hp));

    if (hp < 1) this->Destroy();
}

