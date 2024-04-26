#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerController::ASF_AttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
	AttackerEnemyState = ESF_AttackerEnemyState::Idle;
}

void ASF_AttackerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_AttackerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    MoveTowardsPlayer(DeltaTime);
}

void ASF_AttackerController::MoveTowardsPlayer(const float DeltaTime)
{
    TimeSinceLastAttack += DeltaTime;

    // プレイヤーの位置を参照して突撃する条件を満たすかどうかをチェック
    if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance)
    {
        // 突撃する状態に移行
        if (AttackerEnemyState != ESF_AttackerEnemyState::MovingTowardsPlayer && bCanAttack)
        {
            AttackerEnemyState = ESF_AttackerEnemyState::MovingTowardsPlayer;
            bCanAttack = false; // 突撃を開始したので再びはじめるためにはリセットする必要があります
        }
    }

    // 突撃状態の処理
    if (AttackerEnemyState == ESF_AttackerEnemyState::MovingTowardsPlayer)
    {
        if (!GetCharacter()) return;

        // デバッグメッセージを出力
        Debug::Print("Totugeki");

        // 突撃の方向を計算してAddImpulseを使って突撃する
        FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
        GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
        GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

        // 突撃が完了したら、アイドル状態に移行します
        AttackerEnemyState = ESF_AttackerEnemyState::Idle;
    }

    // 突撃が完了したら再びプレイヤーの位置を見るためにフラグをリセット
    if (AttackerEnemyState == ESF_AttackerEnemyState::Idle && TimeSinceLastAttack >= AttackCooldown)
    {
        bCanAttack = true;
        TimeSinceLastAttack = 0.0f; // リセット
        GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    }
}


/////////////////////////////FORCEINLINE
ASF_GameMode* ASF_AttackerController::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* ASF_AttackerController::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}