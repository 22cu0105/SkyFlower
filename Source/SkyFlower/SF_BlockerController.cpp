#include "SF_BlockerController.h"
#include "SF_BlockerEnemy.h"
#include "SF_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SF_CharacterBase.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_BlockerController::ASF_BlockerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_BlockerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_BlockerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SF_BlockerEnemy = Cast<ASF_BlockerEnemy>(InPawn);
}

void ASF_BlockerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("Tick"));

	UpdateState(DeltaTime);
	ChooseActionByState(DeltaTime);
}

void ASF_BlockerController::Normal(const float InDeltaTime)
{
    // 時間に基づいた振動を加える
    FVector Offset = FVector(
        Amplitude * FMath::Sin(Frequency * GetWorld()->TimeSeconds),
        Amplitude * FMath::Cos(Frequency * GetWorld()->TimeSeconds),
        0.0f
    );

    // キャラクターの位置に振動を加える
    FVector NewLocation = SF_BlockerEnemy->GetActorLocation() + Offset;
    SF_BlockerEnemy->SetActorLocation(NewLocation);

    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

void ASF_BlockerController::ShortRangeAttack(const float InDeltaTime)
{
}

void ASF_BlockerController::LongRangeAttack(const float InDeltaTime)
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
    FVector SpawnLocation = EnemyLocation + Direction * ProjectileOffset;
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
void ASF_BlockerController::UpdateState(const float InDeltaTime)
{
    if (!SF_BlockerEnemy)return;
    if (!GetPlayerCharacter())return;

    auto PlayerCharacter = GetPlayerCharacter();

    if (SF_BlockerEnemy->GetCharacterState() != ESF_CharacterState::Normal)return;

    // プレイヤーと自分の直線距離を計算
    auto dis = FVector::Dist(PlayerCharacter->GetActorLocation(), SF_BlockerEnemy->GetActorLocation());

    // ステート反映
    if (dis <= SF_BlockerEnemy->GetAttackableDistance_LongRange() && GetCanAttack())
    {
        SF_BlockerEnemy->SetCharacterState(ESF_CharacterState::LongRangeAttack);
    }
}

/// <summary>
/// 現在のステートから行動を決定
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_BlockerController::ChooseActionByState(const float InDeltaTime)
{
    if (!SF_BlockerEnemy)return;
    if (!GetPlayerCharacter())return;

    switch (SF_BlockerEnemy->GetCharacterState()) {
    case ESF_CharacterState::Normal:
    {
        UpdateOnNormal(InDeltaTime);
        break;
    }
    case ESF_CharacterState::BeginAttack:
    {
        SF_BlockerEnemy->SetCharacterState(ESF_CharacterState::Normal);
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

void ASF_BlockerController::UpdateOnNormal(const float InDeltaTime)
{

    TimeSinceLastAttack += InDeltaTime;
    Normal(InDeltaTime);

    // 攻撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (TimeSinceLastAttack >= SF_BlockerEnemy->GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // リセット
    }
}

void ASF_BlockerController::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_BlockerController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    ShortRangeAttack(InDeltaTime);
    OnEndAttack();
}

void ASF_BlockerController::UpdateOnLongRangeAttack(const float InDeltaTime)
{
    LongRangeAttack(InDeltaTime);
    OnEndAttack();
}

void ASF_BlockerController::OnEndAttack()
{
    SetCanAttack(false);
    SF_BlockerEnemy->SetCharacterState(ESF_CharacterState::Normal);
}

void ASF_BlockerController::OnBeginDead()
{
}

void ASF_BlockerController::UpdateOnDead(const float InDeltaTime)
{
}

void ASF_BlockerController::OnEndDead()
{
}
