#include "SF_EffectSpawner.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

USF_EffectSpawner::USF_EffectSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;

}

/// @brief エフェクト生成処理
/// @param InEffectInfo 生成するエフェクトの情報
/// @param InLocation   生成する座標
void USF_EffectSpawner::SpawnEffect(const FSF_EffectInfo& InEffectInfo, const FVector& InLocation)
{
	if (!IsValid(InEffectInfo.EffectData)) return;

	// Particle か Niagara で処理を分ける
	if (UParticleSystem* const Particle = Cast<UParticleSystem>(InEffectInfo.EffectData))
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, FRotator::ZeroRotator, InEffectInfo.Size);
	else if (UNiagaraSystem* const Niagara = Cast<UNiagaraSystem>(InEffectInfo.EffectData))
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, InLocation, FRotator::ZeroRotator, InEffectInfo.Size);
}