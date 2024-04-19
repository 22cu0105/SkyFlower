// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_Magicball.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class SKYFLOWER_API ASF_Magicball : public AActor
{
	GENERATED_BODY()
	///////////////////////////// override function	
public:	
	ASF_Magicball();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

	///////////////////////////// custom function
public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

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





};
