// ==================================================
// Filename	:	SF_AttackerController.h
// Author	:	22cu0115 ç‚â∫ëÒêl
// Description: éÂêlåˆÇ…ìÀä—ÇµÇƒÇ≠ÇÈìG
// Notes:		ó·
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyControllerBase.h"
#include "SF_AttackerController.generated.h"



UCLASS()
class SKYFLOWER_API ASF_AttackerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()
	
public:
    ASF_AttackerController();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
    float ChasePower = 5000.0f;

    float TimeSinceLastAttack = 0.f;
    float AttackCooldown = 2.0f; // ìÀåÇä‘äu
    bool bCanAttack = true;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:
    // Function to move AI towards the player
    void StateCheck(const float DeltaTime);
    void StateSwitch();
    void Idle();
    void Move();
    void BeginAttack();
    void MoveAttack();
    void ShortRangeAttack();
    void LongRangeAttack();

    // Distance within which the AI will start chasing the player
    UPROPERTY(EditAnywhere)
        float ChaseDistance = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "TEST")
        TSubclassOf<AActor> ProjectileClass;
};
