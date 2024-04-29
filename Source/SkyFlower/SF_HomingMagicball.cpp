// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_HomingMagicball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "SF_Player.h"
#include "SF_EnemyBase.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"  

// Sets default values
ASF_HomingMagicball::ASF_HomingMagicball()// get LockOnTarget from player
	: target(nullptr)
	, hitDamage(50.f)
	, accelerateDelta(300)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->InitSphereRadius(20.0f);

	SphereComp->OnComponentHit.AddDynamic(this, &ASF_HomingMagicball::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASF_HomingMagicball::OnBeginOverlap);
	InitialLifeSpan = 4.0f;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;

	MovementComp->bIsHomingProjectile = true;
	MovementComp->HomingAccelerationMagnitude = 2000.f;
}

// Called when the game starts or when spawned
void ASF_HomingMagicball::BeginPlay()
{
	Super::BeginPlay();

	// find an enemy on the map as target
	if (!target)
	{
		for (TActorIterator<ASF_EnemyBase> It(GetWorld()); It; ++It)
		{
			ASF_EnemyBase* FoundEnemy = *It;
			if (FoundEnemy)
			{
				target = FoundEnemy;
				break; // stop searching
			}
		}

		if (!target)
		{
			Debug::PrintFixedLine("NO ENEMY FOR HOMING ATTACK", 65);
			this->Destroy();
		}
	}

	USceneComponent* targetRootComponent = target->GetRootComponent();
	MovementComp->HomingTargetComponent = targetRootComponent;
}

void ASF_HomingMagicball::InitTarget(ASF_EnemyBase* targetenemy)
{
	target = targetenemy;
}

// Called every frame
void ASF_HomingMagicball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!target) return;

	float accelerationTemp = MovementComp->HomingAccelerationMagnitude;
	accelerationTemp += accelerateDelta;
	accelerationTemp = FMath::Clamp(accelerationTemp, /* min */0.0f, /* max */ 3000.0f);
	MovementComp->HomingAccelerationMagnitude = accelerationTemp;

}

void ASF_HomingMagicball::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void ASF_HomingMagicball::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::PrintFixedLine("HomingMagicbal OnBeginOverlap", 46);

	//filter
	if (OtherActor == nullptr || OtherActor == this) return;
	if (OtherActor->IsA<ASF_Player>()) return;

	//debug
	DRAW_SPHERE(GetActorLocation());

	//spawn explosion
	if (ParticleEffect)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);
	}

	//apply damage
	ISF_DamageableInterface* damageInterface = Cast<ISF_DamageableInterface>(OtherActor);
	if (damageInterface)
	{
		damageInterface->GetDamage(hitDamage);
	}


	this->Destroy();

}



