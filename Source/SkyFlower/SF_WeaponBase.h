// ==================================================
// Filename	:	SF_WeaponBase.h
// Author	:	22cu0115 坂下拓人
// Description: プレイヤーが持ってる武器の情報
// Notes:		例
//				
// Update:		
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "SF_EquipmentBase.h"
#include "SF_WeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class SKYFLOWER_API ASF_WeaponBase : public ASF_EquipmentBase
{
	GENERATED_BODY()

public:
	ASF_WeaponBase();

protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		float hitDamage = 20;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* BoxComponent;

public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "TEST")
		UParticleSystem* ParticleEffect;

	UBoxComponent* GetBoxComponent() { return BoxComponent; }
};
