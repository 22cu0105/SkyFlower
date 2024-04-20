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

	// 敵を追いかける
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

	// 計測開始
	moveTime += DeltaTime;

	// 位置を取得する
	playerPos = GetPlayerCharacter()->GetActorLocation();
	enemyPos = GetGameMode()->GetRockOnEnemyPos();

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