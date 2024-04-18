// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0115 坂下拓人
// Description: 攻撃の関数定義
// Update	:	2024/04/09
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_AttackInput.generated.h"

class ASF_GameMode;
class ASF_Player;

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

	// 敵を追いかける速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float moveSpeed = 2500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeLimit = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float moveTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAtDestination = false;
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

	UFUNCTION()
		void MoveToEnemy(float DeltaTime);

	////////////////////////////////////////// Get関数
	FORCEINLINE ASF_GameMode* GetGameMode() const;

	FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
