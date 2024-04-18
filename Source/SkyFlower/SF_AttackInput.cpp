#include "SF_AttackInput.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "DebugHelpers.h"
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
	
	// “G‚ð’Ç‚¢‚©‚¯‚é
	MoveToEnemy(DeltaTime);
}

void USF_AttackInput::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;
	
	Debug::PrintFixedLine("BeginNormalAttack()");

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::BeginAttack);

	isAtDestination = true;

	// ŽžŠÔ‘ª‚é GetWorld()->GetDeltaSeconds();
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
	//		LaserAttack();
	// }
}

void USF_AttackInput::EndNormalAttack()
{
	if (!GetPlayerCharacter()) return;
	
	Debug::PrintFixedLine("EndNormalAttack()");
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

	// AppllyDamage(Enemy);
}

void USF_AttackInput::LongRangeAttack()
{
	if (!GetPlayerCharacter()) return;
	// if (!IsValid(SF_Player)) return;

	GetPlayerCharacter()->SetCharacterState(ESF_CharacterState::LongRangeAttack);

	// AppllyDamage(Enemy);
}

void USF_AttackInput::MoveToEnemy(float DeltaTime)
{
	if (isAtDestination)
	{
		moveTime += DeltaTime;
		// “G‚ÌˆÊ’u‚ðŽæ“¾‚·‚é
		//FVector EnemyLocation = NearestEnemy->GetActorLocation();
		FVector EnemyLocation(0, 100, 100);

		// ƒvƒŒƒCƒ„[‚ª“G‚É‹ß‚Ã‚­•ûŒü‚ðŒvŽZ‚·‚é
		FVector DirectionToEnemy = (EnemyLocation - GetPlayerCharacter()->GetActorLocation()).GetSafeNormal();

		// ƒvƒŒƒCƒ„[‚ð“G‚ÉŒü‚©‚Á‚ÄˆÚ“®‚³‚¹‚é
		FVector NewLocation = FMath::VInterpConstantTo(GetPlayerCharacter()->GetActorLocation() + DirectionToEnemy,
			EnemyLocation, DeltaTime, moveSpeed);
		GetPlayerCharacter()->SetActorLocation(NewLocation);

		if (GetPlayerCharacter()->GetActorLocation() == EnemyLocation || moveTime >= timeLimit)
		{
			isAtDestination = false;
			moveTime = 0.f;
		}
	}
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