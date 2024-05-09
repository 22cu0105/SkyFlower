#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "SF_AttackerEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SF_CharacterBase.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerController::ASF_AttackerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASF_AttackerController::BeginPlay()
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("BeginPlaydayooooo"));
}

void ASF_AttackerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    SF_AttackerEnemy = Cast<ASF_AttackerEnemy>(InPawn);
}

void ASF_AttackerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateState(DeltaTime);
    ChooseActionByState(DeltaTime);
}

void ASF_AttackerController::Normal(const float InDeltaTime)
{
    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

void ASF_AttackerController::ShortRangeAttack(const float InDeltaTime)
{
    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();

    GetCharacter()->GetCharacterMovement()->StopMovementImmediately();

}

void ASF_AttackerController::LongRangeAttack(const float InDeltaTime)
{
    // 突撃の方向を計算してAddImpulseを使って突撃する
    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();

    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

/// <summary>
/// ステートを更新する関数 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_AttackerController::UpdateState(const float InDeltaTime)
{
    if (!SF_AttackerEnemy)return;
    if (!GetPlayerCharacter())return;
    auto PlayerCharacter = GetPlayerCharacter();
    if (SF_AttackerEnemy->GetCharacterState() != ESF_CharacterState::Normal)return;

    // プレイヤーと自分の直線距離を計算
    auto dis = FVector::Dist(PlayerCharacter->GetActorLocation(), SF_AttackerEnemy->GetActorLocation());

    // ステート反映
    if (dis <= SF_AttackerEnemy->GetAttackableDistance_ShortRange() && GetCanAttack())
    {
        SF_AttackerEnemy->SetCharacterState(ESF_CharacterState::ShortRangeAttack);
    }
    else if (dis <= SF_AttackerEnemy->GetAttackableDistance_LongRange() && GetCanAttack())
    {
        SF_AttackerEnemy->SetCharacterState(ESF_CharacterState::LongRangeAttack);
    }
}

/// <summary>
/// 現在のステートから行動を決定
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_AttackerController::ChooseActionByState(const float InDeltaTime)
{
    if (!SF_AttackerEnemy)return;
    if (!GetPlayerCharacter())return;

    switch (SF_AttackerEnemy->GetCharacterState()) {
    case ESF_CharacterState::Normal:
    {
        UpdateOnNormal(InDeltaTime);
        break;
    }
    case ESF_CharacterState::BeginAttack:
    {
        SF_AttackerEnemy->SetCharacterState(ESF_CharacterState::Normal);
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

void ASF_AttackerController::UpdateOnNormal(const float InDeltaTime)
{

    TimeSinceLastAttack += InDeltaTime;
    Normal(InDeltaTime);

    // 攻撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= SF_AttackerEnemy->GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // リセット
    }
}

void ASF_AttackerController::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_AttackerController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    ShortRangeAttack(InDeltaTime);
    SF_AttackerEnemy->AttackCollision(20);
    OnEndAttack();
}

void ASF_AttackerController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
    LongRangeAttack(InDeltaTime);

    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), SF_AttackerEnemy->GetActorLocation());

    // ここは変える予定
    if (dis <= SF_AttackerEnemy->GetAttackableDistance_ShortRange())
    {
        OnEndAttack();
    }
}

void ASF_AttackerController::OnEndAttack()
{
    SetCanAttack(false);
    SF_AttackerEnemy->SetCharacterState(ESF_CharacterState::Normal);
}

void ASF_AttackerController::OnBeginDead()
{
}

void ASF_AttackerController::UpdateOnDead(const float InDeltaTime)
{
}

void ASF_AttackerController::OnEndDead()
{
}


