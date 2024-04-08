// ==================================================
// Filename	:	SF_MoveInput.h
// Author	:	22cu0115 ç‚â∫ëÒêl
// Description: à⁄ìÆÇÃä÷êîíËã`
// Notes:		ó·
//				
// Update:		2024/04/05 22cu0115 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_MoveInput.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_MoveInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_MoveInput();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void MoveForward(const float InValue);
	void MoveRight(const float InValue);
	void MoveUp(const float InValue);
};
