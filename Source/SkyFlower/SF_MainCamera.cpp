#include "SF_MainCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ASF_MainCamera::ASF_MainCamera()
	: CameraState(ESF_CameraState::None)
	, ViewPoint(FVector(0.f))
	, MaxPitch(20.f)
{
	PrimaryActorTick.bCanEverTick = true;

	if (IsValid(SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"))))
	{
		SpringArmComponent->SetupAttachment(RootComponent);
		SpringArmComponent->TargetArmLength = 0.f;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bEnableCameraLag = true;
	}

	if (IsValid(CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"))))
	{
		CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
		CameraComponent->AspectRatio = 1.95f;
	}
}

void ASF_MainCamera::BeginPlay()
{
	Super::BeginPlay();

	CameraState = ESF_CameraState::Normal;
	
	if (APlayerController* const PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		PlayerController->SetViewTargetWithBlend(this);

	if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		ViewPoint = Player->GetActorLocation();
}

void ASF_MainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ToDo
	switch (CameraState)
	{
	case ESF_CameraState::Normal:
		if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			ViewPoint = Player->GetActorLocation();
			SetActorLocation(ViewPoint);
		}
		break;
	case ESF_CameraState::NormalBattle:
		if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			ViewPoint = Player->GetActorLocation();
			SetActorLocation(ViewPoint);
		}
		break;
	case ESF_CameraState::CloseBattle:
		// EnemyManager���烍�b�N�I�������G�̏����󂯎��A
		// ���̓G�ƃv���C���[�̍��W�̒��S�𒍎��_�ɂ���
		if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			ViewPoint = Player->GetActorLocation();
			SetActorLocation(ViewPoint);
		}
		break;
	}
	
}

/// @brief Pitch�̉�]����
/// @param InValue ��]��
void ASF_MainCamera::AddPitchRotation(float InValue)
{
	if (InValue == 0.f) return;

	// ���݂̃J�����̉�]�ʂɉ��Z
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += InValue;

	// �␳
	if (NewRotation.Pitch >= MaxPitch)
		NewRotation.Pitch = MaxPitch;
	else if (NewRotation.Pitch <= -MaxPitch)
		NewRotation.Pitch = -MaxPitch;

	// �K�p
	SetActorRotation(NewRotation);
}

/// @brief Yaw�̉�]����
/// @param InValue ��]��
void ASF_MainCamera::AddYawRotation(float InValue)
{
	if (InValue == 0.f) return;

	// ���݂̃J�����̉�]�ʂɉ��Z
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += InValue;

	// �K�p
	SetActorRotation(NewRotation);
}