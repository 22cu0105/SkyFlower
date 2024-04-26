// ==================================================
// Filename	:	SF_HomingMagicball.h
// Author	:	22cu0214 JinWener
// Description: Homing�U���p���@�e
// Notes:		
//				
// Update:		2024/04/26 22cu0214 create
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_HomingMagicball.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class ASF_EnemyBase;

UCLASS()
class SKYFLOWER_API ASF_HomingMagicball : public AActor
{
	GENERATED_BODY()
	
	///////////////////////////// override function	
public:
	ASF_HomingMagicball(/*ASF_EnemyBase* targetEnemy = nullptr*/);
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

	///////////////////////////// custom function
public:
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
	//void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///////////////////////////// custom variable
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, Category = "TEST")
	UParticleSystem* ParticleEffect;

private:
	ASF_EnemyBase* target;
	int32 hitDamage;
	float accelerate;
};