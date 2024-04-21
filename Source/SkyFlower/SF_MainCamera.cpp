#include "SF_MainCamera.h"
#include "SF_Player.h"
#include "SF_GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SF_PlayerController.h"

ASF_MainCamera::ASF_MainCamera()
	: CameraState(ESF_CameraState::None)
	, ViewPoint(FVector(0.f))
	, MaxPitch(20.f)
	, CurrentCameraEventType(ESF_CameraEventType::None)
	, FOVInfoMap()
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

	// 初期化
	if (ASF_GameMode* const SF_GameMode = Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		SF_GameMode->SetMainCamera(this);

		if (ASF_Player* const SF_Player = SF_GameMode->GetPlayerCharacter())
			ViewPoint = SF_Player->GetActorLocation();
	}	
	
	
	APlayerController* const PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
		PlayerController->SetViewTargetWithBlend(this);

	ASF_PlayerController* CustomController = Cast<ASF_PlayerController>(PlayerController);
	if (CustomController)
		CustomController->SetMainCamera(this);

	CameraState = ESF_CameraState::Normal;

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
		// EnemyManagerからロックオンした敵の情報を受け取り、
		// その敵とプレイヤーの座標の中心を注視点にする
		if (APawn* const Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			ViewPoint = Player->GetActorLocation();
			SetActorLocation(ViewPoint);
		}
		break;
	}

	// ToDo
	switch (CurrentCameraEventType)
	{
	case ESF_CameraEventType::Dash:
		// FOV
		if (FSF_CameraInfo* const CurrentFOVInfo = FOVInfoMap.Find(CurrentCameraEventType))
		{
			switch (CurrentFOVInfo->CurrentMode)
			{
			case ESF_AddValueMode::Add:
				if (FSF_ChangeValueInfo* const CurrentChangeValueInfo = CurrentFOVInfo->InfoMap.Find(ESF_AddValueMode::Add))
				{
					CurrentChangeValueInfo->CurrentValue += CurrentChangeValueInfo->AddValue;
					if (CurrentChangeValueInfo->CurrentValue > CurrentChangeValueInfo->MaxOrMinValue)
						CurrentFOVInfo->CurrentMode = ESF_AddValueMode::Reduce;
				}
				break;
			case ESF_AddValueMode::Reduce:
				if (FSF_ChangeValueInfo* const CurrentChangeValueInfo = CurrentFOVInfo->InfoMap.Find(ESF_AddValueMode::Add))
				{
					CurrentChangeValueInfo->CurrentValue -= CurrentChangeValueInfo->AddValue;
					if (CurrentChangeValueInfo->CurrentValue < CurrentChangeValueInfo->MaxOrMinValue)
						CurrentFOVInfo->CurrentMode = ESF_AddValueMode::None;
				}
				break;
			}
		}
		break;
	}
}

/// @brief Pitchの回転処理
/// @param InValue 回転量
void ASF_MainCamera::AddPitchRotation(float InValue)
{
	if (InValue == 0.f) return;

	// 現在のカメラの回転量に加算
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += InValue;

	// 補正
	if (NewRotation.Pitch >= MaxPitch)
		NewRotation.Pitch = MaxPitch;
	else if (NewRotation.Pitch <= -MaxPitch)
		NewRotation.Pitch = -MaxPitch;

	// 適用
	SetActorRotation(NewRotation);
}

/// @brief Yawの回転処理
/// @param InValue 回転量
void ASF_MainCamera::AddYawRotation(float InValue)
{
	if (InValue == 0.f) return;

	// 現在のカメラの回転量に加算
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += InValue;

	// 適用
	SetActorRotation(NewRotation);
}