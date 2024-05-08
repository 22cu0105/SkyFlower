#include "SF_ShooterController.h"
#include "SF_Player.h"
#include "SF_ShooterEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_ShooterController::ASF_ShooterController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASF_ShooterController::BeginPlay()
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("BeginPlaydayooooo"));
}

void ASF_ShooterController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    SF_ShooterEnemy = Cast<ASF_ShooterEnemy>(InPawn);
}

void ASF_ShooterController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateState(DeltaTime);
    ChooseActionByState(DeltaTime);
}

void ASF_ShooterController::Normal(const float InDeltaTime)
{
    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

void ASF_ShooterController::ShortRangeAttack(const float InDeltaTime)
{
    // 突撃の方向を計算してAddImpulseを使って突撃する
    FVector Direction = -(GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();

    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();

    GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

void ASF_ShooterController::LongRangeAttack(const float InDeltaTime)
{
    // ProjectileClassとGetPawn()のnullチェックを行う
    if (!ProjectileClass || !GetPawn()) return;

    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    GetCharacter()->GetCharacterMovement()->StopMovementImmediately();

    // 敵の位置とプレイヤーの位置を取得し、方向ベクトルを計算
    FVector EnemyLocation = GetPawn()->GetActorLocation();
    FVector TargetLocation = GetPlayerCharacter()->GetActorLocation();
    FVector Direction = (TargetLocation - EnemyLocation).GetSafeNormal();

    // 方向ベクトルから回転を計算し、敵の向きをプレイヤーの方向に変更
    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);

    // プロジェクタイルのスポーン位置を計算（EnemyLocationの少し前方に移動）
    float Distance = 100.0f; // 前方に移動する距離を設定
    FVector SpawnLocation = EnemyLocation + Direction * Distance;
    FTransform SpawnTM = FTransform(Rotation, SpawnLocation);

    // プロジェクタイルをスポーンさせる
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.Instigator = GetPawn();
    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

/// <summary>
/// ステートを更新する関数 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterController::UpdateState(const float InDeltaTime)
{
    if (!SF_ShooterEnemy)return;
    if (!GetPlayerCharacter())return;
    if (SF_ShooterEnemy->GetCharacterState() != ESF_CharacterState::Normal)return;
    auto PlayerCharacter = GetPlayerCharacter();
    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(PlayerCharacter->GetActorLocation(), SF_ShooterEnemy->GetActorLocation());

    // ステート反映
    if (dis <= SF_ShooterEnemy->GetAttackableDistance_ShortRange() && GetCanAttack())
    {
        SF_ShooterEnemy->SetCharacterState(ESF_CharacterState::ShortRangeAttack);
    }
    else if (dis <= SF_ShooterEnemy->GetAttackableDistance_LongRange() && GetCanAttack())
    {
        SF_ShooterEnemy->SetCharacterState(ESF_CharacterState::LongRangeAttack);
    }

}

/// <summary>
/// 現在のステートから行動を決定
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterController::ChooseActionByState(const float InDeltaTime)
{
    if (!SF_ShooterEnemy)return;
    if (!GetPlayerCharacter())return;

    switch (SF_ShooterEnemy->GetCharacterState()) {
    case ESF_CharacterState::Normal:
    {
        UpdateOnNormal(InDeltaTime);
        break;
    }
    case ESF_CharacterState::BeginAttack:
    {
        SF_ShooterEnemy->SetCharacterState(ESF_CharacterState::Normal);
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

void ASF_ShooterController::UpdateOnNormal(const float InDeltaTime)
{
    Normal(InDeltaTime);

    TimeSinceLastAttack += InDeltaTime;

    // 攻撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // リセット
    }
}

void ASF_ShooterController::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_ShooterController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    ShortRangeAttack(InDeltaTime);

    // プレイヤーと自分の直線距離を計算
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), SF_ShooterEnemy->GetActorLocation());

    // ステート反映
    if (dis <= SF_ShooterEnemy->GetAttackableDistance_LongRange() && GetCanAttack())
    {
        OnEndAttack();
    }
}

void ASF_ShooterController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
    LongRangeAttack(InDeltaTime);
    OnEndAttack();
}

void ASF_ShooterController::OnEndAttack()
{
    SetCanAttack(false);
    SF_ShooterEnemy->SetCharacterState(ESF_CharacterState::Normal);
}

void ASF_ShooterController::OnBeginDead()
{
}

void ASF_ShooterController::UpdateOnDead(const float InDeltaTime)
{
}

void ASF_ShooterController::OnEndDead()
{
}

