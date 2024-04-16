// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0115 ç‚â∫ëÒêl
// Description: çUåÇÇÃä÷êîíËã`
// Update	:	2024/04/09
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_AttackInput.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_AttackInput : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_AttackInput();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BeginNormalAttack();
	void EndNormalAttack();
	void HomingAttack();
	void LaserAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	void ShortRangeAttack();
	void LongRangeAttack();
};
