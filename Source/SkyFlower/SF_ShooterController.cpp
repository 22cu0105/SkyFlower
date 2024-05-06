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
    // �ˌ��̕������v�Z����AddImpulse���g���ēˌ�����
    FVector Direction = -(GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();

    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();

    GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);
}

void ASF_ShooterController::LongRangeAttack(const float InDeltaTime)
{
    // ProjectileClass��GetPawn()��null�`�F�b�N���s��
    if (!ProjectileClass || !GetPawn()) return;

    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    GetCharacter()->GetCharacterMovement()->StopMovementImmediately();

    // �G�̈ʒu�ƃv���C���[�̈ʒu���擾���A�����x�N�g�����v�Z
    FVector EnemyLocation = GetPawn()->GetActorLocation();
    FVector TargetLocation = GetPlayerCharacter()->GetActorLocation();
    FVector Direction = (TargetLocation - EnemyLocation).GetSafeNormal();

    // �����x�N�g�������]���v�Z���A�G�̌������v���C���[�̕����ɕύX
    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);

    // �v���W�F�N�^�C���̃X�|�[���ʒu���v�Z�iEnemyLocation�̏����O���Ɉړ��j
    float Distance = 100.0f; // �O���Ɉړ����鋗����ݒ�
    FVector SpawnLocation = EnemyLocation + Direction * Distance;
    FTransform SpawnTM = FTransform(Rotation, SpawnLocation);

    // �v���W�F�N�^�C�����X�|�[��������
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.Instigator = GetPawn();
    GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

