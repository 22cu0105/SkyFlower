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

    // �v���C���[�̈ʒu���Q�Ƃ��ēˌ���������𖞂������ǂ������`�F�b�N
    if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(), GetPawn()->GetActorLocation()) <= ChaseDistance)
    {
        // �ˌ������ԂɈڍs
        if (AttackerEnemyState != ESF_AttackerEnemyState::MovingTowardsPlayer && bCanAttack)
        {
            AttackerEnemyState = ESF_AttackerEnemyState::MovingTowardsPlayer;
            bCanAttack = false; // �ˌ����J�n�����̂ōĂт͂��߂邽�߂ɂ̓��Z�b�g����K�v������܂�
        }
    }

    // �ˌ���Ԃ̏���
    if (AttackerEnemyState == ESF_AttackerEnemyState::MovingTowardsPlayer)
    {
        if (!GetCharacter()) return;

        // �f�o�b�O���b�Z�[�W���o��
        Debug::Print("Totugeki");

        // �ˌ��̕������v�Z����AddImpulse���g���ēˌ�����
        FVector Direction = (GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();
        GetCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
        GetCharacter()->GetCharacterMovement()->AddImpulse(Direction * ChasePower, true);

        // �ˌ�������������A�A�C�h����ԂɈڍs���܂�
        AttackerEnemyState = ESF_AttackerEnemyState::Idle;
    }

    // �ˌ�������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
    if (AttackerEnemyState == ESF_AttackerEnemyState::Idle && TimeSinceLastAttack >= AttackCooldown)
    {
        bCanAttack = true;
        TimeSinceLastAttack = 0.0f; // ���Z�b�g
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