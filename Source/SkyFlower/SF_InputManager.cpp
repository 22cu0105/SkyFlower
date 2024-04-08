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

	// ...
}


void USF_InputManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void USF_InputManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USF_InputManager::SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent)
{
	if (!IsValid(InPlayerInputComponent)) return;

	InPlayerInputComponent->BindAxis("MoveForward", this, &USF_InputManager::MoveForward);
	InPlayerInputComponent->BindAxis("MoveRight",	this, &USF_InputManager::MoveRight);
	InPlayerInputComponent->BindAxis("MoveUp",		this, &USF_InputManager::MoveUp);
	InPlayerInputComponent->BindAxis("LookUp",		this, &USF_InputManager::LookUp);
	InPlayerInputComponent->BindAxis("Turn",		this, &USF_InputManager::Turn);

	InPlayerInputComponent->BindAction("Attack",IE_Pressed,this, &USF_InputManager::Attack);

	UE_LOG(LogTemp, Warning, TEXT("InputManager : SetupPlayerInputComponent"));
}

void USF_InputManager::LookUp(const float InValue)
{
}

void USF_InputManager::Turn(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if (ASF_MainCamera* const SF_Camera = SF_GameMode->GetMainCamera())
			SF_Camera->AddYawRotation(InValue);
}

void USF_InputManager::MoveForward(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if (ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter())
			SF_Player->MoveForward(InValue);
}

void USF_InputManager::MoveRight(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if (ASF_Player* SF_Player = SF_GameMode->GetPlayerCharacter())
			SF_Player->MoveRight(InValue);
}

void USF_InputManager::MoveUp(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if (ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter())
			SF_Player->MoveUp(InValue);
}

void USF_InputManager::Attack()
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if (ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter())
			SF_Player->Attack();
}

