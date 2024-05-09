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

    //// 敵の実際の行動
    //SF_ShooterController = Cast<ASF_ShooterController>(GetOwner());
}

void ASF_ShooterEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //UpdateState(DeltaTime);
    //ChooseActionByState(DeltaTime);
}

/// <summary>
/// ステートを更新する関数 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterEnemy::UpdateState(const float InDeltaTime)
{
    //if (!IsValid(SF_ShooterController)) return;
    if (GetCharacterState() != ESF_CharacterState::Normal)return;

    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetActorLocation());

    // ステート反映
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
/// 現在のステートから行動を決定
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

    // 攻撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // リセット
    }
}

void ASF_ShooterEnemy::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_ShooterEnemy::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    //SF_ShooterController->ShortRangeAttack(InDeltaTime);
   
    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetActorLocation());

    // ステート反映
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

