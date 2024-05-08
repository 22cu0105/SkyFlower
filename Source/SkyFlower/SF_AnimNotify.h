// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SF_AnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSingNature)
UCLASS()
class SKYFLOWER_API USF_AnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnNotifiedSingNature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
