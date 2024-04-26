// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_PlayerController.h"
#include "SF_Player.h"
#include "SF_MainCamera.h"
#include "SF_GameMode.h"

#include "Kismet/GameplayStatics.h"

ASF_PlayerController::ASF_PlayerController()
	:m_pCharacter(nullptr)
	, m_pCamera(nullptr)
{
}

void ASF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* pPawn = GetPawn();
	ensure(pPawn != nullptr);
	m_pCharacter = Cast<ASF_Player>(pPawn);
	ensure(m_pCharacter != nullptr);

	ASF_GameMode* const GameMode =
		Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	ensure(GameMode != nullptr);
	m_pCamera = GameMode->GetMainCamera();
}

void ASF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//movement process
	InputComponent->BindAxis("MoveForward", this, &ASF_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASF_PlayerController::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &ASF_PlayerController::MoveUp);
	InputComponent->BindAxis("Turn", this, &ASF_PlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ASF_PlayerController::LookUp);
	InputComponent->BindAction("MoveDash", IE_Pressed, this, &ASF_PlayerController::MoveDash);

	//attack process
	InputComponent->BindAction("BeginNormalAttack", IE_Pressed, this, &ASF_PlayerController::BeginNormalAttack);
	InputComponent->BindAction("EndNormalAttack", IE_Released, this, &ASF_PlayerController::EndNormalAttack);
	InputComponent->BindAction("HomingAttack", IE_Pressed, this, &ASF_PlayerController::HomingAttack);
	InputComponent->BindAction("LaserAttack", IE_Pressed, this, &ASF_PlayerController::LaserAttack);

}

///////////////////////// camera
void ASF_PlayerController::LookUp(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddPitchRotation(InValue);
}

void ASF_PlayerController::Turn(const float InValue)
{
	if (!m_pCamera) return;
	m_pCamera->AddYawRotation(InValue);

}

///////////////////////// Player movement
void ASF_PlayerController::MoveForward(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveForward(InValue);
}

void ASF_PlayerController::MoveRight(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveRight(InValue);
}

void ASF_PlayerController::MoveUp(const float InValue)
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveUp(InValue);
}

void ASF_PlayerController::MoveDash()
{
	if (!m_pCharacter) return;
	m_pCharacter->MoveDash();
}

///////////////////////// Player attack
void ASF_PlayerController::BeginNormalAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->BeginNormalAttack();

}

void ASF_PlayerController::EndNormalAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->EndNormalAttack();

}

void ASF_PlayerController::HomingAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->HomingAttack();

}

void ASF_PlayerController::LaserAttack()
{
	if (!m_pCharacter) return;
	m_pCharacter->LaserAttack();

}