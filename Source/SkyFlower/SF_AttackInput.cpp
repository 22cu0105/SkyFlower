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

	// �G��ǂ�������
	MoveToEnemy(DeltaTime);
}

void USF_AttackInput::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("BeginNormalAttack()", 15);

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	// ���ԑ��� GetWorld()->GetDeltaSeconds();
	// if(pressedTime <= 3)
	// {
	//		GetGameMode()->getRockOnEnemy()
	// 		if (EnemyPos - PlayerPos < ShortRange)
	//		{
	// 		ShortRangeAttack();
	// 		}
	// 		else 
	//		{
	// 		LongRangeAttack();
	//		}
	// }
	// else
	// {
	//		LaserAttack();
	// }

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

void USF_AttackInput::EndNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("EndNormalAttack()");
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

	isAtDestination = true;

	// AppllyDamage(Enemy);
}

void USF_AttackInput::LongRangeAttack()
{
	if (!GetPlayerCharacter()) return;
	// if (!IsValid(SF_Player)) return;

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::LongRangeAttack);

	// AppllyDamage(Enemy);
}

void USF_AttackInput::MoveToEnemy(float DeltaTime)
{
	if (isAtDestination)
	{
		// �v���J�n
		moveTime += DeltaTime;

		// �G�̈ʒu���擾����
		//FVector EnemyLocation = NearestEnemy->GetActorLocation();
		const FVector EnemyLocation(0, 100, 100);

		// �v���C���[���G�ɋ߂Â��������v�Z����
		const FVector DirectionToEnemy = (EnemyLocation - GetPlayerCharacter()->GetActorLocation()).GetSafeNormal();

		// �v���C���[��G�Ɍ������Ĉړ�������
		const FVector NewLocation = FMath::VInterpConstantTo(GetPlayerCharacter()->GetActorLocation() + DirectionToEnemy,
			EnemyLocation, DeltaTime, moveSpeed);

		// ��]
		const FRotator currentRot = { 0.f, GetPlayerCharacter()->GetActorRotation().Yaw, 0.f };
		const FRotator targetRot = { 0.f, DirectionToEnemy.Rotation().Yaw, 0.f };

		GetPlayerCharacter()->SetActorLocation(NewLocation);
		GetPlayerCharacter()->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, DeltaTime, 20.f));

		if (GetPlayerCharacter()->GetActorLocation() == EnemyLocation || moveTime >= timeLimit)
		{
			isAtDestination = false;
			moveTime = 0.f;
		}
	}
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