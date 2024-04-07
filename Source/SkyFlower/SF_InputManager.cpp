#include "SF_InputManager.h"

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

void USF_InputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!IsValid(PlayerInputComponent)) return;

	PlayerInputComponent->BindAxis("MoveForward", this, &USF_InputManager::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",	  this, &USF_InputManager::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",	  this, &USF_InputManager::LookUp);
	PlayerInputComponent->BindAxis("Turn",		  this, &USF_InputManager::Turn);
}

void USF_InputManager::LookUp(const float InValue)
{
}

void USF_InputManager::Turn(const float InValue)
{
}

void USF_InputManager::MoveForward(const float InValue)
{
}

void USF_InputManager::MoveRight(const float InValue)
{
}
