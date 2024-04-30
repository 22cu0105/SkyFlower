#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerController::ASF_AttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
	SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_AttackerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    StateCheck(DeltaTime);

    StateSwitch();
}

/// <summary>
/// ステート変更
/// </summary>
/// <param name="DeltaTime"></param>
void ASF_AttackerController::StateCheck(const float DeltaTime)
{
    TimeSinceLastAttack += DeltaTime;

    // プレイヤーの位置を参照して突撃する条件を満たすかどうかをチェック
    if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance)
    {
        // 突撃する状態に移行
        if (GetEnemyState() != ESF_EnemyState::Move && bCanAttack)
        {
            SetEnemyState(ESF_EnemyState::Move);
            bCanAttack = false;
        }
    }
    else if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance * 2)
    {
        // 突撃する状態に移行
        if (GetEnemyState() != ESF_EnemyState::LongRangeAttack && bCanAttack)
        {
            SetEnemyState(ESF_EnemyState::LongRangeAttack);
            bCanAttack = false;
        }
    }
}

/// <summary>
/// ステートごとの処理
/// </summary>
void ASF_AttackerController::StateSwitch()
{
    switch (GetEnemyState()) {
    case ESF_EnemyState::Idle:
    {
        Idle();
        break;
    }
    case ESF_EnemyState::Move:
    {
        Move();
        break;
    }
    case ESF_EnemyState::BeginAttack:
    {
        BeginAttack();
        break;
    }
    case ESF_EnemyState::MoveAttack:
    {
        MoveAttack();
        break;
    }
    case ESF_EnemyState::ShortRangeAttack:
    {
        ShortRangeAttack();
        break;
    }
    case ESF_EnemyState::LongRangeAttack:
    {
        LongRangeAttack();
        break;
    }
    default:
    {
        break;
    }
    }
}

void ASF_AttackerController::Idle()
{
    // 突撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= AttackCooldown)
    {
        bCanAttack = true;
        TimeSinceLastAttack = 0.0f; // リセット
        GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    }
}

void ASF_AttackerController::Move()
{
    if (!GetCharacter()) return;

    // デバッグメッセージを出力
    Debug::Print("Totugeki");

    // 突撃の方向を計算してAddImpulseを使って突撃する
    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);

    // 敵の状態をアイドルに変更
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::BeginAttack()
{
    // 敵の状態をアイドルに変更
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::MoveAttack()
{
    // 敵の状態をアイドルに変更
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::ShortRangeAttack()
{
    // 敵の状態をアイドルに変更
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::LongRangeAttack()
{
    // ProjectileClassとGetPawn()のnullチェックを行う
    if (!ProjectileClass || !GetPawn()) return;

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

    // 敵の状態をアイドルに変更
    SetEnemyState(ESF_EnemyState::Idle);
}

