#include "SF_FlockerController.h"
#include "DebugHelpers.h"

ASF_FlockerController::ASF_FlockerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASF_FlockerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_FlockerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
