#include "SF_AttackInput.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelpers.h"

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

void USF_AttackInput::BeginNormalAttack()
{
	Debug::PrintFixedLine("NormalAttack()");

	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());

		if (!IsValid(SF_Player)) return;

		SF_Player->SetCharacterState(ESF_CharacterState::BeginAttack);
	}

	//ŽžŠÔ‘ª‚é
	// if(pressedTime <= 3)
	// {
	//		getGameMode()->getRockOnEnemy()
	// 		if (EnemyPos - PlayerPos < ShortRange)
	//		{
	// 		ShortRangeAttack();
	// 		}
	// 		else 
	//		{
	// 		LongRangeAttack();
	//		}
	// }
	// else
	// {
	//		LaserAttack()
	// }
}

void USF_AttackInput::EndNormalAttack()
{

}

void USF_AttackInput::HomingAttack()
{
	Debug::PrintFixedLine("HomingAttack()");
}

void USF_AttackInput::LaserAttack()
{
	Debug::PrintFixedLine("LaserAttack()");
}

void USF_AttackInput::ShortRangeAttack()
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());

		if (!IsValid(SF_Player)) return;

		SF_Player->SetCharacterState(ESF_CharacterState::ShortRangeAttack);
	}
}

void USF_AttackInput::LongRangeAttack()
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());

		if (!IsValid(SF_Player)) return;

		SF_Player->SetCharacterState(ESF_CharacterState::LongRangeAttack);


	}
}