// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_Magicball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASF_Magicball::ASF_Magicball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void ASF_Magicball::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(this, true);
}

// Called every frame
void ASF_Magicball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASF_Magicball::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr || OtherActor == this) return;

	DRAW_SPHERE(GetActorLocation());

	if (ParticleEffect)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);
	}

	this->Destroy();
}
