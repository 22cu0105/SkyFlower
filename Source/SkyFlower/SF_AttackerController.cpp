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
/// �X�e�[�g�ύX
/// </summary>
/// <param name="DeltaTime"></param>
void ASF_AttackerController::StateCheck(const float DeltaTime)
{
    TimeSinceLastAttack += DeltaTime;

    // �v���C���[�̈ʒu���Q�Ƃ��ēˌ���������𖞂������ǂ������`�F�b�N
    if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance)
    {
        // �ˌ������ԂɈڍs
        if (GetEnemyState() != ESF_EnemyState::Move && bCanAttack)
        {
            SetEnemyState(ESF_EnemyState::Move);
            bCanAttack = false;
        }
    }
    else if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance * 2)
    {
        // �ˌ������ԂɈڍs
        if (GetEnemyState() != ESF_EnemyState::LongRangeAttack && bCanAttack)
        {
            SetEnemyState(ESF_EnemyState::LongRangeAttack);
            bCanAttack = false;
        }
    }
}

/// <summary>
/// �X�e�[�g���Ƃ̏���
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
    // �ˌ�������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
    if (TimeSinceLastAttack >= AttackCooldown)
    {
        bCanAttack = true;
        TimeSinceLastAttack = 0.0f; // ���Z�b�g
        GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    }
}

void ASF_AttackerController::Move()
{
    if (!GetCharacter()) return;

    // �f�o�b�O���b�Z�[�W���o��
    Debug::Print("Totugeki");

    // �ˌ��̕������v�Z����AddImpulse���g���ēˌ�����
    FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
    GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
    GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

    FRotator Rotation = Direction.Rotation();
    GetPawn()->SetActorRotation(Rotation);

    // �G�̏�Ԃ��A�C�h���ɕύX
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::BeginAttack()
{
    // �G�̏�Ԃ��A�C�h���ɕύX
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::MoveAttack()
{
    // �G�̏�Ԃ��A�C�h���ɕύX
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::ShortRangeAttack()
{
    // �G�̏�Ԃ��A�C�h���ɕύX
    SetEnemyState(ESF_EnemyState::Idle);
}

void ASF_AttackerController::LongRangeAttack()
{
    // ProjectileClass��GetPawn()��null�`�F�b�N���s��
    if (!ProjectileClass || !GetPawn()) return;

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

    // �G�̏�Ԃ��A�C�h���ɕύX
    SetEnemyState(ESF_EnemyState::Idle);
}

