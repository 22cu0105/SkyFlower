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

class ASF_GameMode;
class ASF_Player;

UCLASS()
class SKYFLOWER_API ASF_AttackerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()
	
public:
    ASF_AttackerController();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Function to move AI towards the player
    void MoveTowardsPlayer();

    // Distance within which the AI will start chasing the player
    UPROPERTY(EditAnywhere)
    float ChaseDistance = 1000.0f;

public:
    ////////////////////////////////////////// Getä÷êî
    FORCEINLINE ASF_GameMode* GetGameMode() const;

    FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
