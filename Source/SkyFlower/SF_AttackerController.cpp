#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerController::ASF_AttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyState = ESF_EnemyState::Idle;
}

void ASF_AttackerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_AttackerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Move(DeltaTime);
}

void ASF_AttackerController::Move(const float DeltaTime)
{
    TimeSinceLastAttack += DeltaTime;

    // �v���C���[�̈ʒu���Q�Ƃ��ēˌ���������𖞂������ǂ������`�F�b�N
    if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance)
    {
        // �ˌ������ԂɈڍs
        if (EnemyState != ESF_EnemyState::Move && bCanAttack)
        {
            EnemyState = ESF_EnemyState::Move;
            bCanAttack = false;
        }
    }
    else if(FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance * 2)
    {
        // �ˌ������ԂɈڍs
        if (EnemyState != ESF_EnemyState::LongRangeAttack && bCanAttack)
        {
            EnemyState = ESF_EnemyState::LongRangeAttack;
            bCanAttack = false;
        }
    }

    // �X�e�[�g���Ƃ̏���
    switch (GetEnemyState()){
        case ESF_EnemyState::Move:
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

            // �ˌ�������������A�A�C�h����ԂɈڍs���܂�
            EnemyState = ESF_EnemyState::Idle;
            break;
        }

        case ESF_EnemyState::LongRangeAttack:
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
            EnemyState = ESF_EnemyState::Idle;
            break;

        }

        case ESF_EnemyState::Idle:
        {
            // �ˌ�������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
            if (TimeSinceLastAttack >= AttackCooldown)
            {
                bCanAttack = true;
                TimeSinceLastAttack = 0.0f; // ���Z�b�g
                GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

