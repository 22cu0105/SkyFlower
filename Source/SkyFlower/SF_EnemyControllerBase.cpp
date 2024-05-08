#include "SF_EnemyControllerBase.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include <Kismet/GameplayStatics.h>

ASF_EnemyControllerBase::ASF_EnemyControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_EnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASF_EnemyControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ASF_EnemyControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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

