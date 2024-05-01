#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"
#include "SF_MoveInput.h"
#include "SF_AttackInput.h"
#include "SF_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelpers.h"
using namespace Debug;

ASF_Player::ASF_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	// コンポーネント生成
	MoveInputComponent = CreateDefaultSubobject<USF_MoveInput>(TEXT("MoveInputComponent"));
	AttackInputComponent = CreateDefaultSubobject<USF_AttackInput>(TEXT("AttackInputComponent"));
}

void ASF_Player::BeginPlay()
{
	Super::BeginPlay();

	if (ASF_GameMode* SF_GameMode =
		Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SF_GameMode->SetPlayerCharacter(this);
	}

	if (ASF_PlayerController* CustomController =
		Cast<ASF_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) {
		CustomController->SetPlayerCharacter(this);
	}
}

void ASF_Player::GetDamage(int32 damage)
{
	Debug::PrintFixedLine("GetDamage Player");
}

/// @brief プレイヤーの状態を常に変更
void ASF_Player::UpdateSetPlayerState()
{
	ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(SF_GameMode)) return;

	ASF_EnemyBase* const LockOnEnemy = SF_GameMode->GetLockOnEnemy();
	// ターゲットが設定されていなければ通常状態
	if (!IsValid(SF_GameMode->GetLockOnEnemy()))
	{
		Debug::PrintFixedLine("not found LockOnEnemy");
		SetCharacterState(ESF_CharacterState::Normal);
		return;
	}

	// 敵とプレイヤーの距離を取得し、遠距離・近距離かで状態を変化させる
	float Distance = (LockOnEnemy->GetActorLocation() - GetActorLocation()).Length();
	if (Distance < GetAttackableDistance_LongRange())
	{
		if (Distance < GetAttackableDistance_ShortRange())
		{
			Debug::PrintFixedLine("ShortRange");
			SetCharacterState(ESF_CharacterState::ShortRangeAttack);
		}
		else
		{
			Debug::PrintFixedLine("LongRange");
			SetCharacterState(ESF_CharacterState::LongRangeAttack);
		}
	}
	// 射程外ならロックオンを解除し通常状態にする
	else
	{
		Debug::PrintFixedLine("out LongRange");
		SF_GameMode->SetLockOnEnemy(nullptr);
		SetCharacterState(ESF_CharacterState::Normal);
	}
}

void ASF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSetPlayerState();
}

void ASF_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	//	SF_GameMode->SetupPlayerInputComponent(PlayerInputComponent);
}

void ASF_Player::MoveForward(const float InValue)
{
	if (!IsValid(MoveInputComponent)) return;

	MoveInputComponent->MoveForward(InValue);
}

void ASF_Player::MoveRight(const float InValue)
{
	if (!IsValid(MoveInputComponent)) return;

	MoveInputComponent->MoveRight(InValue);
}

void ASF_Player::MoveDash()
{
	if (!IsValid(MoveInputComponent)) return;

	MoveInputComponent->MoveDash();
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SF_GameMode->GetMainCamera()->StartCameraEvent(ESF_CameraEventType::Dash);
	}
}

void ASF_Player::MoveUp(const float InValue)
{
	if (!IsValid(MoveInputComponent)) return;

	MoveInputComponent->MoveUp(InValue);
}

void ASF_Player::BeginNormalAttack()
{
	if (!IsValid(AttackInputComponent)) return;

	AttackInputComponent->BeginNormalAttack();

	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		// ロックオンが設定されていたら終了
		if (IsValid(SF_GameMode->GetLockOnEnemy()))
		{
			Debug::Print("setted lock on enemy");
			return;
		}

		ASF_EnemyBase* const Enemy = SF_GameMode->GetNearestEnemy();
		if (!IsValid(Enemy))
		{
			Debug::Print("not found nearest enemy");
			return;
		}

		float Distance = (Enemy->GetActorLocation() - GetActorLocation()).Length();
		if (Distance < GetAttackableDistance_LongRange())
		{
			Debug::Print("LockOn");
			SF_GameMode->SetLockOnEnemy(Enemy);
		}
	}
}

void ASF_Player::EndNormalAttack()
{
	if (!IsValid(AttackInputComponent)) return;

	AttackInputComponent->EndNormalAttack();
}

void ASF_Player::HomingAttack()
{
	if (!IsValid(AttackInputComponent)) return;

	AttackInputComponent->HomingAttack();
}

void ASF_Player::LaserAttack()
{
	if (!IsValid(AttackInputComponent)) return;

	AttackInputComponent->LaserAttack();

	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		// ロックオンが設定されていたら終了
		if (IsValid(SF_GameMode->GetLockOnEnemy()))
		{
			Debug::Print("setted lock on enemy");
			return;
		}

		ASF_EnemyBase* const Enemy = SF_GameMode->GetNearestEnemy();
		if (!IsValid(Enemy)) 
		{
			Debug::Print("not found nearest enemy");
			return;
		}

		float Distance = (Enemy->GetActorLocation() - GetActorLocation()).Length();
		if (Distance < GetAttackableDistance_LongRange())
		{
			Debug::Print("LockOn");
			SF_GameMode->SetLockOnEnemy(Enemy);
		}
	}
}
