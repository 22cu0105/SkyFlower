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
    // ���ԂɊ�Â����U����������
    FVector Offset = FVector(
        Amplitude * FMath::Sin(Frequency * GetWorld()->TimeSeconds),
        Amplitude * FMath::Cos(Frequency * GetWorld()->TimeSeconds),
        0.0f
    );

    // �L�����N�^�[�̈ʒu�ɐU����������
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
    FVector SpawnLocation = EnemyLocation + Direction * ProjectileOffset;
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
void ASF_BlockerController::UpdateState(const float InDeltaTime)
{
    if (!SF_BlockerEnemy)return;
    if (!GetPlayerCharacter())return;

    auto PlayerCharacter = GetPlayerCharacter();

    if (SF_BlockerEnemy->GetCharacterState() != ESF_CharacterState::Normal)return;

    // �v���C���[�Ǝ����̒����������v�Z
    auto dis = FVector::Dist(PlayerCharacter->GetActorLocation(), SF_BlockerEnemy->GetActorLocation());

    // �X�e�[�g���f
    if (dis <= SF_BlockerEnemy->GetAttackableDistance_LongRange() && GetCanAttack())
    {
        SF_BlockerEnemy->SetCharacterState(ESF_CharacterState::LongRangeAttack);
    }
}

/// <summary>
/// ���݂̃X�e�[�g����s��������
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

    // �U��������������Ăуv���C���[�̈ʒu�����邽�߂Ƀt���O�����Z�b�g
    if (TimeSinceLastAttack >= SF_BlockerEnemy->GetAttackCooldown())
    {
        SetCanAttack(true);
        TimeSinceLastAttack = 0.0f; // ���Z�b�g
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
