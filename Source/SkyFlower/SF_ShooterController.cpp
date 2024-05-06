#include "SF_ShooterController.h"
#include "SF_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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

