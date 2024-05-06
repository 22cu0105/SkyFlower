// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_Magicball.h"
#include "DebugHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "SF_Player.h"

// Sets default values
ASF_Magicball::ASF_Magicball()
	:hitDamage(20)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->InitSphereRadius(20.0f);
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SphereComp->OnComponentHit.AddDynamic(this, &ASF_Magicball::OnHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASF_Magicball::OnBeginOverlap);
	InitialLifeSpan = 4.0f;

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
	/*
	if (OtherActor == nullptr || OtherActor == this) return;

	DRAW_SPHERE(GetActorLocation());

	if (ParticleEffect)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);
	}

	this->Destroy();
	*/

	Debug::PrintFixedLine("Magicball OnHit", 45);


}

void ASF_Magicball::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::PrintFixedLine("Magicball OnBeginOverlap", 46);
	
	//filter
	if (OtherActor == nullptr || OtherActor == this) return;
	if (OtherActor->IsA<ASF_Player>()) return;

	//debug
	DRAW_SPHERE(GetActorLocation());
	if (OtherActor != nullptr && OtherActor != this)
	{
		FString ActorName = OtherActor->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("HitActor: %s"), *ActorName);
		Debug::Print(ActorName);
	}

	//apply damage
	ISF_DamageableInterface* damageInterface = Cast<ISF_DamageableInterface>(OtherActor);
	if (damageInterface)
	{
		damageInterface->GetDamage(hitDamage);

		//spawn explosion
		if (ParticleEffect)
		{
			FVector Location = GetActorLocation();
			FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, Rotation, true);

			this->Destroy();
		}
	}
}
