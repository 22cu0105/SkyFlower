// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 坂下 拓人
//				22cu0105 小田島 稜人
// 
// Description:入力処理を各Actor,Characterに送る
// Update	:	2024/04/08
// ==================================================
#include "SF_InputManager.h"
#include "SF_GameMode.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "Kismet/GameplayStatics.h"

USF_InputManager::USF_InputManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USF_InputManager::BeginPlay()
{
	Super::BeginPlay();
}


void USF_InputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USF_InputManager::SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent)
{
	if (!IsValid(InPlayerInputComponent)) return;

	//movement process
	InPlayerInputComponent->BindAxis("MoveForward", this, &USF_InputManager::MoveForward);
	InPlayerInputComponent->BindAxis("MoveRight", this, &USF_InputManager::MoveRight);
	InPlayerInputComponent->BindAxis("MoveUp", this, &USF_InputManager::MoveUp);
	InPlayerInputComponent->BindAxis("LookUp", this, &USF_InputManager::LookUp);
	InPlayerInputComponent->BindAxis("Turn", this, &USF_InputManager::Turn);

	//attack process
	InPlayerInputComponent->BindAction("BeginNormalAttack", IE_Pressed, this, &USF_InputManager::BeginNormalAttack);
	InPlayerInputComponent->BindAction("EndNormalAttack", IE_Released, this, &USF_InputManager::EndNormalAttack);
	InPlayerInputComponent->BindAction("HomingAttack", IE_Pressed, this, &USF_InputManager::HomingAttack);
	InPlayerInputComponent->BindAction("LaserAttack", IE_Pressed, this, &USF_InputManager::LaserAttack);

	UE_LOG(LogTemp, Warning, TEXT("InputManager : SetupPlayerInputComponent"));
}

void USF_InputManager::LookUp(const float InValue)
{

}

void USF_InputManager::Turn(const float InValue)
{
	if (!GetMainCamera()) return;
	GetMainCamera()->AddYawRotation(InValue);
}

void USF_InputManager::MoveForward(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->MoveForward(InValue);
}

void USF_InputManager::MoveRight(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->MoveRight(InValue);
}

void USF_InputManager::MoveUp(const float InValue)
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->MoveUp(InValue);
}

void USF_InputManager::BeginNormalAttack()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->BeginNormalAttack();
}

void USF_InputManager::EndNormalAttack()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->EndNormalAttack();
}

void USF_InputManager::HomingAttack()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->HomingAttack();
}

void USF_InputManager::LaserAttack()
{
	if (!GetPlayerCharacter()) return;
	GetPlayerCharacter()->LaserAttack();
}


/////////////////////////////FORCEINLINE
ASF_GameMode* USF_InputManager::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_MainCamera* USF_InputManager::GetMainCamera() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetMainCamera();
}

ASF_Player* USF_InputManager::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}


