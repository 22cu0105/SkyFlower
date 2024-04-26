// ==================================================
// Filename	:	SF_AttackerController.h
// Author	:	22cu0115 坂下拓人
// Description: 主人公に突貫してくる敵
// Notes:		例
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EnemyControllerBase.h"
#include "SF_AttackerController.generated.h"

class ASF_GameMode;
class ASF_Player;

UENUM(BlueprintType)
enum class ESF_AttackerEnemyState : uint8
{
    Idle                UMETA(DisplayName = "なし"),
    MovingTowardsPlayer UMETA(DisplayName = "移動"),
    Attacking           UMETA(DisplayName = "攻撃"),
};

UCLASS()
class SKYFLOWER_API ASF_AttackerController : public ASF_EnemyControllerBase
{
	GENERATED_BODY()
	
public:
    ASF_AttackerController();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
    float ChasePower = 5000.0f;

    float TimeSinceLastAttack = 0.f;
    float AttackCooldown = 2.0f; // 突撃間隔
    bool bCanAttack = true;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;


private:
    // Function to move AI towards the player
    void MoveTowardsPlayer(const float DeltaTime);

    // Distance within which the AI will start chasing the player
    UPROPERTY(EditAnywhere)
    float ChaseDistance = 1000.0f;

    // エネミーの状態
    UPROPERTY(VisibleAnywhere, Category = "Visible | State")
    ESF_AttackerEnemyState AttackerEnemyState;

public:
    ////////////////////////////////////////// Get関数
    FORCEINLINE ASF_GameMode* GetGameMode() const;

    FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
