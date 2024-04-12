#include "SF_EnemyBase.h"
#include "SF_Player.h"
#include "SF_EnemyControllerBase.h"
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
}

void ASF_EnemyBase::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

}
