// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_AttackerEnemy.h"
#include "SF_AttackerController.h"
#include "SF_GameMode.h"
#include "SF_Player.h"
#include "DebugHelpers.h"

ASF_AttackerEnemy::ASF_AttackerEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_AttackerEnemy::BeginPlay()
{
	Super::BeginPlay();

    // 敵の実際の行動
    SF_AttackerController = Cast<ASF_AttackerController>(GetOwner());
}

void ASF_AttackerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    UpdateState(DeltaTime);
    ChooseActionByState(DeltaTime);
}

/// <summary>
/// ステートを更新する関数 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_AttackerEnemy::UpdateState(const float InDeltaTime)
{
    if (!IsValid(SF_AttackerController)) return;
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
void ASF_AttackerEnemy::ChooseActionByState(const float InDeltaTime)
{
    if (!IsValid(SF_AttackerController)) return;

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

void ASF_AttackerEnemy::UpdateOnNormal(const float InDeltaTime)
{

    TimeSinceLastAttack += InDeltaTime;
    SF_AttackerController->Normal(InDeltaTime);

    // 攻撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // リセット
    }
}

void ASF_AttackerEnemy::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_AttackerEnemy::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    SF_AttackerController->ShortRangeAttack(InDeltaTime);
    AttackCollision(20);
    OnEndAttack();
}

void ASF_AttackerEnemy::UpdateOnLongRangeAttack(const float InDeltaTime)
{
    SF_AttackerController->LongRangeAttack(InDeltaTime);

    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetActorLocation());

    // ここは変える予定
    if (dis <= GetAttackableDistance_ShortRange())
    {
        OnEndAttack();
    }
}

void ASF_AttackerEnemy::OnEndAttack()
{
    SetCanAttack(false);
    SetCharacterState(ESF_CharacterState::Normal);
}

void ASF_AttackerEnemy::OnBeginDead()
{
}

void ASF_AttackerEnemy::UpdateOnDead(const float InDeltaTime)
{
}

void ASF_AttackerEnemy::OnEndDead()
{
}

void ASF_AttackerEnemy::GetDamage(int32 damage)
{
	hp -= damage;
	Debug::Print("EnemyMiddle GetDamage : " + FString::FromInt(hp));

	if (hp < 1) this->Destroy();
}

