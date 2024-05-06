#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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


