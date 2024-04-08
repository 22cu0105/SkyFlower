#include "SF_AttackInput.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

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
}

void USF_AttackInput::Attack()
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());
		
		if (!IsValid(SF_Player)) return;

		SF_Player->SetCharacterState(ESF_CharacterState::BeginAttack);
	}
}

