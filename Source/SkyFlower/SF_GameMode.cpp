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
#include "SF_Player.h"
#include "Kismet/GameplayStatics.h"


ASF_GameMode::ASF_GameMode()
	: bIsInHitStop(false)
	, HitStopSpeed(0.5f)
	, HitStopTime(0.f)
	, Timer_HitStop(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	InputManager = CreateDefaultSubobject<USF_InputManager>(TEXT("InputManager"));
}

void ASF_GameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInHitStop)
	{
		// ヒットストップ時にも一定のDeltaTimeの値にする
		Timer_HitStop += DeltaTime * (1.f / HitStopSpeed);
		if (Timer_HitStop > HitStopTime)
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
			bIsInHitStop = false;
			Timer_HitStop = 0.f;
			HitStopTime = 0.f;
		}
	}
}

void ASF_GameMode::SetupPlayerInputComponent(UInputComponent* const InPlayerInputComponent)
{
	if (!IsValid(InputManager)) return;

	InputManager->SetupPlayerInputComponent(InPlayerInputComponent);
}

// ヒットストップの速度、　ヒットストップさせる時間
void ASF_GameMode::StartHitStop(const float InHitStopSpeed, const float InHitStopTime)
{
	HitStopTime = 0.f;

	HitStopSpeed = InHitStopSpeed;
	HitStopTime = InHitStopTime;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), HitStopSpeed);
	bIsInHitStop = true;
}