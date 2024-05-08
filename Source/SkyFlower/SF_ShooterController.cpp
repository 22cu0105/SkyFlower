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

/// <summary>
/// �X�e�[�g���X�V����֐� 
/// </summary>
/// <param name="InDeltaTime"></param>
void ASF_ShooterController::UpdateState(const float InDeltaTime)
{
    if (!SF_ShooterEnemy)return;
    if (!GetPlayerCharacter())return;
    if (SF_ShooterEnemy->GetCharacterState() != ESF_CharacterState::Normal)return;
    auto PlayerCharacter = GetPlayerCharacter();
    // �v���C���[�Ǝ����̒����������v�Z
    const auto dis = FVector::Dist(PlayerCharacter->GetActorLocation(), SF_ShooterEnemy->GetActorLocation());

    // �X�e�[�g���f
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
/// ���݂̃X�e�[�g����s��������
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

    // �U��������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
    if (TimeSinceLastAttack >= GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // ���Z�b�g
    }
}

void ASF_ShooterController::OnBeginAttack()
{
    OnEndAttack();
}

void ASF_ShooterController::UpdateOnShortRangeAttack(const float InDeltaTime)
{
    ShortRangeAttack(InDeltaTime);

    // �v���C���[�Ǝ����̒����������v�Z
    const auto dis = FVector::Dist(GetPlayerCharacter()->GetActorLocation(), SF_ShooterEnemy->GetActorLocation());

    // �X�e�[�g���f
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

