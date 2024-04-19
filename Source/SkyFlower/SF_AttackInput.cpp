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

	// 押されてからの時間を計測してレーザー攻撃かそれ以外を判定する

	// 敵を追いかける
	MoveToEnemy(DeltaTime);
}

void USF_AttackInput::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::PrintFixedLine("BeginNormalAttack()", 15);

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	// 時間測る GetWorld()->GetDeltaSeconds();
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
		// 計測開始
		moveTime += DeltaTime;

		// 敵の位置を取得する
		//FVector EnemyLocation = NearestEnemy->GetActorLocation();
		const FVector EnemyLocation(0, 100, 100);

		// プレイヤーが敵に近づく方向を計算する
		const FVector DirectionToEnemy = (EnemyLocation - GetPlayerCharacter()->GetActorLocation()).GetSafeNormal();

		// プレイヤーを敵に向かって移動させる
		const FVector NewLocation = FMath::VInterpConstantTo(GetPlayerCharacter()->GetActorLocation() + DirectionToEnemy,
			EnemyLocation, DeltaTime, moveSpeed);

		// 回転
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