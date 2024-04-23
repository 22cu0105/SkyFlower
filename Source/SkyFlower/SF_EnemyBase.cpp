#include "SF_EnemyBase.h"
#include "SF_Player.h"
#include "SF_EnemyControllerBase.h"
#include "DebugHelpers.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASF_EnemyBase::ASF_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ASF_EnemyControllerBase* const EnemyController = Cast<ASF_EnemyControllerBase>(GetController());
	// プレイヤー
	ASF_Player* const player = Cast<ASF_Player>(GetOwner());

	if (EnemyController && player)
	{
		// AIControllerにプレイヤー情報を設定
		EnemyController->SetPlayerKey(player);
	}
}

void ASF_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead())
		if (GetCurrentHP() <= 0.f)
			SetCharacterState(ESF_CharacterState::BeginDead);
	
	switch (GetCharacterState())
	{
	case ESF_CharacterState::Normal:
		UpdateOnNormal(DeltaTime);
		break;
	case ESF_CharacterState::BeginDead:
		OnBeginDead();
		break;
	case ESF_CharacterState::Dead:
		UpdateOnDead(DeltaTime);
		break;
	case ESF_CharacterState::EndDead:
		OnEndDead();
		break;
	}
}

void ASF_EnemyBase::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}

/// ToDo
/// @brief 通常時更新処理
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnNormal(const float InDeltaTime)
{

}

/// ToDo
/// @brief 攻撃開始時処理
void ASF_EnemyBase::OnBeginAttack()
{
}

/// ToDo
/// @brief 近接攻撃更新処理
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnShortRangeAttack(const float InDeltaTime)
{
}

/// ToDo
/// @brief 遠距離攻撃更新処理
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnLongRangeAttack(const float InDeltaTime)
{

}

/// @brief 攻撃終了時処理
void ASF_EnemyBase::OnEndAttack()
{
}

/// ToDo
/// @brief 死亡開始時時処理
void ASF_EnemyBase::OnBeginDead()
{
	SetCharacterState(ESF_CharacterState::Dead);
}

/// ToDo
/// @brief 死亡時更新処理
/// @param InDeltaTime 
void ASF_EnemyBase::UpdateOnDead(const float InDeltaTime)
{
	SetCharacterState(ESF_CharacterState::EndDead);
}

/// @brief 死亡終了時処理
void ASF_EnemyBase::OnEndDead()
{
	Destroy();
}

void ASF_EnemyBase::GetDamage(int32 damage)
{
	Debug::PrintFixedLine("GetDamage EnemyBase");
}
