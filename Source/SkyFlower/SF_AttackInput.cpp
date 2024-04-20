#include "SF_AttackInput.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SF_MainCamera.h"


// Sets default values for this component's properties
USF_AttackInput::USF_AttackInput()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USF_AttackInput::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USF_AttackInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ������Ă���̎��Ԃ��v�����ă��[�U�[�U��������ȊO�𔻒肷��
	if (isButtonPressed)
	{
		// �{�^���������ꑱ���Ă��鏈�����s��
		pressedTime += DeltaTime;
	}
	MoveToEnemy(DeltaTime);
}

void USF_AttackInput::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("BeginNormalAttack()", 15);

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	isButtonPressed = true;
}

void USF_AttackInput::EndNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("EndNormalAttack()");

	if (pressedTime < gatherPowerTime)
	{
		playerPos = GetPlayerCharacter()->GetActorLocation();
		enemyPos = GetGameMode()->GetRockOnEnemyPos();
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *enemyPos.ToString());

		// 2�̓_�Ԃ̋����𑪂邽�߂Ƀ��[�N���b�h������2����擾����
		const float DistanceSquared = FVector::DistSquared(playerPos, enemyPos);

		// FMath::Square()�́A�^����ꂽ�l��2����v�Z����
		// �Ȃ����t�B�[���h��ɓG�����Ȃ��ꍇ�v���C���[�̍��W�Ɠ����ɂȂ�
		if (enemyPos == playerPos || DistanceSquared > FMath::Square(attackableDistance))
		{
			LongRangeAttack();
		}
		else if (DistanceSquared <= FMath::Square(attackableDistance))
		{
			ShortRangeAttack();
		}
	}
	// gatherPowerTime�ȏゾ������
	else
	{
		LaserAttack();
	}

	isButtonPressed = false;
	pressedTime = 0;
}

void USF_AttackInput::HomingAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("HomingAttack()");
}

void USF_AttackInput::LaserAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("LaserAttack()");
}

void USF_AttackInput::ShortRangeAttack()
{
	if (!GetPlayerCharacter()) return;

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::ShortRangeAttack);

	UE_LOG(LogTemp, Warning, TEXT("ShortRange"));

	// �G��ǂ�������
	beginShortAttack = true;
}

void USF_AttackInput::LongRangeAttack()
{
	if (!GetPlayerCharacter()) return;
	// if (!IsValid(SF_Player)) return;
	UE_LOG(LogTemp, Warning, TEXT("LongRange"));

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::LongRangeAttack);

	//throw magicball
	FVector HandLocation = GetPlayerCharacter()->GetMesh()->GetSocketLocation("Magicball");

	ASF_MainCamera* camera = GetGameMode()->GetMainCamera();
	FTransform SpawnTM = FTransform(camera->GetActorRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = GetPlayerCharacter();

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	Debug::PrintFixedLine("AttackRanged", 22);
}

void USF_AttackInput::MoveToEnemy(float DeltaTime)
{
	if (!beginShortAttack) return;

	UE_LOG(LogTemp, Warning, TEXT("aaaaaRange"));

	if (stoppingDistance >= FVector::Distance(playerPos, enemyPos) || moveTime >= moveTimeLimit)
	{
		beginShortAttack = false;
		moveTime = 0.f;
		return;
	}

	// �v���J�n
	moveTime += DeltaTime;

	// �ʒu���擾����
	playerPos = GetPlayerCharacter()->GetActorLocation();
	enemyPos = GetGameMode()->GetRockOnEnemyPos();

	// �v���C���[���G�ɋ߂Â��������v�Z����
	const FVector DirectionToEnemy = (enemyPos - playerPos).GetSafeNormal();

	// �v���C���[��G�Ɍ������Ĉړ�������
	const FVector newPos = FMath::VInterpConstantTo(playerPos, enemyPos, DeltaTime, moveSpeed);

	// ��]
	const FRotator currentRot = { 0.f, GetPlayerCharacter()->GetActorRotation().Yaw, 0.f };
	const FRotator targetRot = { 0.f, DirectionToEnemy.Rotation().Yaw, 0.f };

	// �v���C���[�����X�V
	GetPlayerCharacter()->SetActorLocation(newPos);
	GetPlayerCharacter()->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, DeltaTime, rotationSpeed));
}

/////////////////////////////FORCEINLINE
ASF_GameMode* USF_AttackInput::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* USF_AttackInput::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}