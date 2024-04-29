// ==================================================
// Filename	:	SF_EnemyControllerBase.h
// Author	:	22cu0115 âº ñl
// Description: Gl~[ðì·é
// Update	:	2024/04/12
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SF_EnemyControllerBase.generated.h"

class ASF_GameMode;
class ASF_Player;

UENUM(BlueprintType)
enum class ESF_EnemyState : uint8
{
	Idle                UMETA(DisplayName = "Èµ"),
	Move				UMETA(DisplayName = "Ú®"),
	BeginAttack			UMETA(DisplayName = "UJn"),
	ShortRangeAttack	UMETA(DisplayName = "ß£U"),
	LongRangeAttack		UMETA(DisplayName = "£U"),
};

UCLASS()
class SKYFLOWER_API ASF_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// Gl~[ÌóÔ
	UPROPERTY(VisibleAnywhere, Category = "Visible | State")
		ESF_EnemyState EnemyState;
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		ESF_EnemyState GetEnemyState() { return EnemyState; }
	
public:
	////////////////////////////////////////// GetÖ
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
