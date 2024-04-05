// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 â‰º‘ñl
// Description: ˆÚ“®‚ÌŠÖ”’è‹`
// Notes:		—á
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#include "SF_MoveInput.h"
#include "Kismet/KismetSystemLibrary.h" // ’Ç‰Á
#include "Kismet/GameplayStatics.h" // ’Ç‰Á
#include "Components/InputComponent.h" // ’Ç‰Á
#include "EnhancedInputComponent.h" // ’Ç‰Á
#include "EnhancedInputSubsystems.h" // ’Ç‰Á

// Sets default values for this component's properties
USF_MoveInput::USF_MoveInput()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USF_MoveInput::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USF_MoveInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USF_MoveInput::SetupPlayerInputComponent(UEnhancedInputComponent* const EnhancedInputComponent)
{
	//Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &USF_MoveInput::Jump);

	//Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USF_MoveInput::Move);
}

void USF_MoveInput::Move(const FInputActionValue& Value)
{

}

void USF_MoveInput::Jump(const FInputActionValue& Value)
{

}
