// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 �≺��l
// Description: �ړ��̊֐���`
// Notes:		��
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#include "SF_MoveInput.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

USF_MoveInput::USF_MoveInput()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USF_MoveInput::BeginPlay()
{
	Super::BeginPlay();
}

void USF_MoveInput::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());
	const FVector movement = SF_Player->GetLastMovementInputVector();
	// ���͂����鎞������]
	if (movement.X != 0 || movement.Y != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" : %s"), "�ʂ��Ă܂�");
		const FRotator currentRot = {0.f, SF_Player->GetActorRotation().Yaw, 0.f};
		const FRotator targetRot = {0.f, movement.Rotation().Yaw, 0.f};
		SF_Player->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, DeltaTime, rotationSpeed));
	}
}

void USF_MoveInput::MoveForward(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_MainCamera* const SF_MainCamera = SF_GameMode->GetMainCamera();
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());
		
		if (!IsValid(SF_MainCamera)) return;
		if (!IsValid(SF_Player)) return;

		//const FRotator Rotation = {
		//	0.f,
		//	UKismetMathLibrary::FindLookAtRotation(SF_Player->GetActorLocation(),FVector(0.f, InValue * 100.f, 0.f)).Yaw,
		//	0.f };
		//UE_LOG(LogTemp, Warning, TEXT("Forward: %f"), SF_Player->GetActorUpVector());

		// ���͕����Ɉړ�
		SF_Player->AddMovementInput(SF_MainCamera->GetActorForwardVector(), InValue);
	}
}

void USF_MoveInput::MoveRight(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_MainCamera* const SF_MainCamera = SF_GameMode->GetMainCamera();
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());

		if (!IsValid(SF_MainCamera)) return;
		if (!IsValid(SF_Player)) return;	
		
		// ���͕����Ɉړ�
		SF_Player->AddMovementInput(SF_MainCamera->GetActorRightVector(), InValue);
	}
}

void USF_MoveInput::MoveUp(const float InValue)
{
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		ASF_MainCamera* const SF_MainCamera = SF_GameMode->GetMainCamera();
		ASF_Player* const SF_Player = Cast<ASF_Player>(GetOwner());

		if (!IsValid(SF_MainCamera)) return;
		if (!IsValid(SF_Player)) return;

		// ���͕����Ɉړ�
		SF_Player->AddMovementInput(SF_MainCamera->GetActorUpVector(), InValue);
	}
}