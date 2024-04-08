// ==================================================
// Filename	:	SF_GameMode.h
// Author	:	22cu0115 坂下 拓人
//				22cu0105 小田島 稜人
// 
// Description:Playerから送られてくる情報を受け取る
// Update	:	2024/04/08
// ==================================================


#include "SF_GameMode.h"
#include "SF_InputManager.h"


ASF_GameMode::ASF_GameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	InputManager = CreateDefaultSubobject<USF_InputManager>(TEXT("InputManager"));
}

void ASF_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASF_GameMode::SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent)
{
	if (!IsValid(InputManager)) return;

	InputManager->SetupPlayerInputComponent(InPlayerInputComponent);
}


