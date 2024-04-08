#include "SF_Player.h"
#include "SF_GameMode.h"
#include "SF_MoveInput.h"
#include "SF_AttackInput.h"
#include "Kismet/GameplayStatics.h"

ASF_Player::ASF_Player()
{
	PrimaryActorTick.bCanEverTick = false;

	// コンポーネント生成
	MoveInputComponent   = CreateDefaultSubobject<USF_MoveInput>  (TEXT("MoveInputComponent"));
	AttackInputComponent = CreateDefaultSubobject<USF_AttackInput>(TEXT("AttackInputComponent"));
}

void ASF_Player::BeginPlay()
{
	Super::BeginPlay();

	if (ASF_GameMode* SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SF_GameMode->SetPlayerCharacter(this);
	}
}

void ASF_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASF_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		SF_GameMode->SetupPlayerInputComponent(PlayerInputComponent);
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

void ASF_Player::MoveUp(const float InValue)
{
	if (!IsValid(MoveInputComponent)) return;

	MoveInputComponent->MoveUp(InValue);
}

void ASF_Player::Attack()
{

}