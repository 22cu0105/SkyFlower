#include "SF_AttackerController.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "GameFramework/Pawn.h"
#include "DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASF_AttackerController::ASF_AttackerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_AttackerController::BeginPlay()
{
	Super::BeginPlay();

}

void ASF_AttackerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Dist(GetPlayerCharacter()->GetActorLocation(),GetPawn()->GetActorLocation()) <= ChaseDistance)
	{
		//Debug::Print("Attack Kiteruyo");

		MoveTowardsPlayer();
	}
}

void ASF_AttackerController::MoveTowardsPlayer()
{
	// Calculate direction towards the player
	FVector Direction = GetPlayerCharacter()->GetActorLocation() - GetPawn()->GetActorLocation();
	Direction.Normalize();

	// Move AI towards the player
	GetPawn()->AddMovementInput(Direction, 1.0f);
}

/////////////////////////////FORCEINLINE
ASF_GameMode* ASF_AttackerController::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* ASF_AttackerController::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}