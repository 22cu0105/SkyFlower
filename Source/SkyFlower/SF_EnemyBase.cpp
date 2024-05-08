#include "SF_EnemyBase.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "SF_Player.h"
#include "SF_EnemyControllerBase.h"
#include "DebugHelpers.h"
#include "Perception/PawnSensingComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetSystemLibrary.h"

ASF_EnemyBase::ASF_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
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
	
	//switch (GetCharacterState())
	//{
	//case ESF_CharacterState::Normal:
	//	UpdateOnNormal(DeltaTime);
	//	break;
	//case ESF_CharacterState::BeginDead:
	//	OnBeginDead();
	//	break;
	//case ESF_CharacterState::Dead:
	//	UpdateOnDead(DeltaTime);
	//	break;
	//case ESF_CharacterState::EndDead:
	//	OnEndDead();
	//	break;
	//}
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

/////////////////////////////FORCEINLINE
ASF_GameMode* ASF_EnemyBase::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* ASF_EnemyBase::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}