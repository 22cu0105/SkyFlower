// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 坂下拓人
// Description: 移動の関数定義
// Notes:		例
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#include "SF_MoveInput.h"
#include "Kismet/KismetSystemLibrary.h" // 追加
#include "Kismet/GameplayStatics.h" // 追加
#include "Components/InputComponent.h" // 追加
#include "EnhancedInputComponent.h" // 追加
#include "EnhancedInputSubsystems.h" // 追加

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
