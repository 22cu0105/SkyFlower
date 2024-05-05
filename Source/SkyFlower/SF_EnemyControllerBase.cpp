#include "SF_EnemyControllerBase.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include <Kismet/GameplayStatics.h>

/////////////////////////////FORCEINLINE
ASF_GameMode* ASF_EnemyControllerBase::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* ASF_EnemyControllerBase::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}

