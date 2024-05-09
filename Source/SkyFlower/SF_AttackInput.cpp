#include "SF_AttackInput.h"

// for normal attack
#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "SF_GameMode.h"
#include "SF_AnimNotify.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "DebugHelpers.h"

// for homing attack
#include "Kismet/GameplayStatics.h"
#include "SF_MainCamera.h"
#include "SF_FunctionLibrary.h"
#include "SF_HomingMagicball.h"
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "Math/RotationMatrix.h"
#include "SF_EnemyBase.h"
#include "EngineUtils.h"  


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
	if (!GetPlayerCharacter()) return;
	if (!AnimInstance)
	{
		AnimInstance = GetPlayerCharacter()->GetMesh()->GetAnimInstance();
	}

	// 押されてからの時間を計測してレーザー攻撃かそれ以外を判定する
	if (isButtonPressed)
	{
		// ボタンが押され続けている処理を行う
		pressedTime += DeltaTime;
	}
	MoveToEnemy(DeltaTime);
}

void USF_AttackInput::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;

	//GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	isButtonPressed = true;
}

void USF_AttackInput::EndNormalAttack()
{
	if (!GetPlayerCharacter()) return;
	UE_LOG(LogTemp, Log, TEXT("%f"), pressedTime);

	if (pressedTime < gatherPowerTime)
	{
		playerPos = GetPlayerCharacter()->GetActorLocation();
		if (ASF_EnemyBase* const RockOnEnemy = GetGameMode()->GetNearestEnemy())
			enemyPos = RockOnEnemy->GetActorLocation();

		// 2つの点間の距離を測るためにユークリッド距離の2乗を取得する
		const float DistanceSquared = FVector::DistSquared(playerPos, enemyPos);

		// FMath::Square()は、与えられた値の2乗を計算する
		// なぜかフィールド上に敵がいない場合プレイヤーの座標と同じになる
		if (enemyPos == playerPos || DistanceSquared > FMath::Square(attackableDistance))
		{
			LongRangeAttack();
		}
		else if (DistanceSquared <= FMath::Square(attackableDistance))
		{
			ShortRangeAttack();
		}
	}
	// gatherPowerTime以上だったら
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

	Debug::Print("HomingAttack()");

	// to launch HomingMagicballs we need:
	// 0. check Target
	// 1. PlayerForwardDirection as basic Axis
	// 2. LaunchDirection for each HomingMagicball
	// 3. Spawn


	// find Target
	/* TODO get target from LockOn */

	/* step 0 */
	// get an enemy on the map as target 
	ASF_EnemyBase* target = nullptr;
	for (TActorIterator<ASF_EnemyBase> It(GetWorld()); It; ++It)
	{
		ASF_EnemyBase* FoundEnemy = *It;
		if (FoundEnemy)
		{
			target = FoundEnemy;
			break; // stop searching
		}

		if (!IsValid(target))
		{
			Debug::PrintFixedLine("NO ENEMY FOR HOMING ATTACK", 85);
			return;
		}
	}

	/* step 1 */
	// get Axis
	FVector axis = FVector::ZeroVector;
#define AXIS_PLAYER 0
#if AXIS_PLAYER
	axis = USF_FunctionLibrary::GetPlayer(this)->GetActorForwardVector();
#else
	axis = USF_FunctionLibrary::GetGameMode(this)->GetMainCamera()->GetActorForwardVector();
#endif

	/* step 2 */
	// spawnRot = basicDirection + angleDeg + correction
	// calculate basicDirection
	FRotator pitchRotator = FRotator(90.f, 0.f, 0.f);
	FQuat quatRotation = FQuat(pitchRotator);
	FVector basicDirection = quatRotation.RotateVector(axis);
	// calculate angleDeg
	float angleDeg = angleStep / (float)magicballNumber;
	// calculate correction
	float offsetMagnitude = -1.5f;
	FVector correctionVector = axis * offsetMagnitude;

	/* step 3 */
	// spawn position
	FVector spawnPos = USF_FunctionLibrary::GetPlayer(this)->GetActorLocation();
	for (int32 i = 0; i < magicballNumber; i++)
	{
		// calculate rotation
		double angleRadians = (double)FMath::DegreesToRadians(angleDeg * (float)i);
		FQuat quat = FQuat(axis, angleRadians);
		FVector direction = (quat.RotateVector(basicDirection) + correctionVector).GetSafeNormal();
		FRotator spawnRot = FRotationMatrix::MakeFromX(direction).Rotator();

		// spawn
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this->GetOwner();
		spawnParams.Instigator = this->GetOwner()->GetInstigator();

		AActor* projectile = GetWorld()->SpawnActor<AActor>(
			HomingAttackClass, spawnPos, spawnRot, spawnParams);
		Cast<ASF_HomingMagicball>(projectile)->InitTarget(target);
	}

}

void USF_AttackInput::LaserAttack()
{
	if (!GetPlayerCharacter()) return;

	Debug::Print("LaserAttack()");
}

void USF_AttackInput::ShortRangeAttack()
{
	if (!GetPlayerCharacter()) return;

	//GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::ShortRangeAttack);

	UE_LOG(LogTemp, Warning, TEXT("ShortRange"));

	// 敵を追いかける
	beginShortAttack = true;

	// ComboMontageはAnimMontageへのポインタを保持している変数です
	if (ComboMontage && AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ComboMontage"));

		if (!AnimInstance->Montage_IsPlaying(ComboMontage))
		{
			GetPlayerCharacter()->PlayAnimMontage(ComboMontage);
		}
	}

}

void USF_AttackInput::LongRangeAttack()
{
	if (!GetPlayerCharacter()) return;
	// if (!IsValid(SF_Player)) return;
	UE_LOG(LogTemp, Warning, TEXT("LongRange"));

	//GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::LongRangeAttack);

	//throw magicball
	{
		if (!MagicballClass) return;
		FVector HandLocation = GetPlayerCharacter()->GetMesh()->GetSocketLocation("Magicball");

		ASF_MainCamera* camera = GetGameMode()->GetMainCamera();
		FTransform SpawnTM = FTransform(camera->GetActorRotation(), HandLocation);
		ASF_EnemyBase* enemy = GetGameMode()->GetNearestEnemy();
		if (!IsValid(enemy))return;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = GetPlayerCharacter();

		GetWorld()->SpawnActor<AActor>(MagicballClass, SpawnTM, SpawnParams);
		Debug::PrintFixedLine("AttackRanged", 22);
	}
}

void USF_AttackInput::MoveToEnemy(float DeltaTime)
{
	if (!beginShortAttack) return;
	ASF_EnemyBase* enemy = GetGameMode()->GetNearestEnemy();
	if (!IsValid(enemy))return;

	if (stoppingDistance >= FVector::Distance(playerPos, enemyPos) || moveTime >= moveTimeLimit)
	{
		beginShortAttack = false;
		moveTime = 0.f;
		return;
	}

	// 計測開始
	moveTime += DeltaTime;

	// 位置を取得する
	playerPos = GetPlayerCharacter()->GetActorLocation();
	enemyPos = GetGameMode()->GetNearestEnemy()->GetActorLocation();

	// プレイヤーが敵に近づく方向を計算する
	const FVector DirectionToEnemy = (enemyPos - playerPos).GetSafeNormal();

	// プレイヤーを敵に向かって移動させる
	const FVector newPos = FMath::VInterpConstantTo(playerPos, enemyPos, DeltaTime, moveSpeed);

	// 回転
	const FRotator currentRot = { 0.f, GetPlayerCharacter()->GetActorRotation().Yaw, 0.f };
	const FRotator targetRot = { 0.f, DirectionToEnemy.Rotation().Yaw, 0.f };

	// プレイヤー情報を更新
	GetPlayerCharacter()->SetActorLocation(newPos);
	GetPlayerCharacter()->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, DeltaTime, rotationSpeed));
}

void USF_AttackInput::NotifyActivateComboInTime()
{
	// NotifyActivateComboInTimeが呼び出された時の処理をここに記述する
	UE_LOG(LogTemp, Warning, TEXT("NotifyActivateComboInTime"));

}

//void USF_AttackInput::NotifyDisActivateComboInTime()
//{
//	// NotifyDisActivateComboInTimeが呼び出された時の処理をここに記述する
//}
//
//void USF_AttackInput::NotifyCheckJumpSection()
//{
//	// NotifyCheckJumpSectionが呼び出された時の処理をここに記述する
//}

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