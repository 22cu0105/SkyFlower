// ==================================================
// Filename	:	SF_MoveInput.cpp
// Author	:	22cu0115 坂下拓人
// Description: 移動の関数定義
// Notes:		例
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#include "SF_MoveInput.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

using namespace Debug;

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
}

void USF_MoveInput::MoveForward(const float InValue)
{
	if (!IsValid(GetMainCamera())) return;
	if (!IsValid(GetPlayerCharacter())) return;

	//const FRotator Rotation = {
	//	0.f,
	//	UKismetMathLibrary::FindLookAtRotation(SF_Player->GetActorLocation(),FVector(0.f, InValue * 100.f, 0.f)).Yaw,
	//	0.f };
	//UE_LOG(LogTemp, Warning, TEXT("Forward: %f"), SF_Player->GetActorUpVector());

	// 入力方向に移動
	GetPlayerCharacter()->AddMovementInput(GetMainCamera()->GetActorForwardVector(), InValue);

	// 回転
	CharacterRotate();
}

void USF_MoveInput::MoveRight(const float InValue)
{
	if (!IsValid(GetMainCamera())) return;
	if (!IsValid(GetPlayerCharacter())) return;

	// 入力方向に移動
	GetPlayerCharacter()->AddMovementInput(GetMainCamera()->GetActorRightVector(), InValue);

	// 回転
	CharacterRotate();
}

void USF_MoveInput::MoveDash()
{
	if (!IsValid(GetMainCamera())) return;
	if (!IsValid(GetPlayerCharacter())) return;

	//UE_LOG(LogTemp, Warning, TEXT(": %f"), GetPlayerCharacter()->GetCharacterMovement()->Velocity;);
	Debug::PrintFixedLine(GetPlayerCharacter()->GetCharacterMovement()->Velocity.ToString());
	
	AddForce(GetPlayerCharacter()->GetActorForwardVector());
}

void USF_MoveInput::MoveUp(const float InValue)
{
	if (!IsValid(GetMainCamera())) return;
	if (!IsValid(GetPlayerCharacter())) return;

	// 入力方向に移動
	GetPlayerCharacter()->AddMovementInput(GetMainCamera()->GetActorUpVector(), InValue);
}

void USF_MoveInput::AddForce(const FVector InDirection)
{
	// プレイヤーの速度を０にする
	GetPlayerCharacter()->GetCharacterMovement()->Velocity = FVector::Zero();
	// ダッシュ
	//UE_LOG(LogTemp, Warning, TEXT("AddForce()"))
	GetPlayerCharacter()->GetCharacterMovement()->AddImpulse(InDirection * dashSpeed, true);
}

void USF_MoveInput::CharacterRotate() const
{
	if (!IsValid(GetPlayerCharacter())) return;

	const FVector movement = GetPlayerCharacter()->GetLastMovementInputVector();

	// 入力がある時だけ回転
	if (movement.X != 0 || movement.Y != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" : %s"), "rotation");
		const FRotator currentRot = { 0.f, GetPlayerCharacter()->GetActorRotation().Yaw, 0.f };
		const FRotator targetRot = { 0.f, movement.Rotation().Yaw, 0.f };
		GetPlayerCharacter()->SetActorRotation(FMath::RInterpTo(currentRot, targetRot, GetWorld()->GetDeltaSeconds(), rotationSpeed));
	}
}

/////////////////////////////FORCEINLINE
ASF_GameMode* USF_MoveInput::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_MainCamera* USF_MoveInput::GetMainCamera() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetMainCamera();
}

ASF_Player* USF_MoveInput::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}