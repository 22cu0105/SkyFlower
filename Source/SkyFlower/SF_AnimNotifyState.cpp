#include "SF_AnimNotifyState.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "SF_GameMode.h"
#include "SF_Player.h"
#include "SF_WeaponBase.h"
#include <Kismet/GameplayStatics.h>



USF_AnimNotifyState::USF_AnimNotifyState()
{
	
}

void USF_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyBegin"));
	//ASF_WeaponBase* SF_WeaponBase = GetPlayerCharacter()->GetWeapon();
	//if (!SF_WeaponBase) return;
	//CollisionBoxComponent = SF_WeaponBase->GetBoxComponent();
	//if (!CollisionBoxComponent)return;
	//// ƒRƒŠƒWƒ‡ƒ“‚ð—LŒø‚É‚·‚é
	//CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
   
}

void USF_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyEnd"));
	if (!CollisionBoxComponent)return;

	CollisionBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void USF_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}


/////////////////////////////FORCEINLINE
ASF_GameMode* USF_AnimNotifyState::GetGameMode() const
{
	return Cast<ASF_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

ASF_Player* USF_AnimNotifyState::GetPlayerCharacter() const
{
	if (!GetGameMode()) return nullptr;
	return GetGameMode()->GetPlayerCharacter();
}
