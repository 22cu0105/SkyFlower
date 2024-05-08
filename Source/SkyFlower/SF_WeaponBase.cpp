#include "SF_WeaponBase.h"
#include "SF_Player.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelpers.h"


ASF_WeaponBase::ASF_WeaponBase()
{
	// ボックスコリジョンを作成し、設定
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASF_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ボックスコリジョンが有効であれば、当たり判定を追加する
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASF_WeaponBase::OnBeginOverlap);
	}
}

void ASF_WeaponBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//filter
	if (OtherActor == nullptr || OtherActor == this) return;
	if (OtherActor->IsA<ASF_Player>()) return;

	UE_LOG(LogTemp, Warning, TEXT("ASF_WeaponBase : OnBeginOverlap"));

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

			//this->Destroy();
		}
	}
}
