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


// Sets default values
ASF_HomingMagicball::ASF_HomingMagicball(/*ASF_EnemyBase* targetEnemy*/)
	//: target(/*targetEnemy*/nullptr)
	//, hitDamage(50.f)
	//, accelerate(300)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->InitSphereRadius(20.0f);

	//SphereComp->OnComponentHit.AddDynamic(this, &ASF_HomingMagicball::OnHit);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASF_HomingMagicball::OnBeginOverlap);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ASF_HomingMagicball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASF_HomingMagicball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

