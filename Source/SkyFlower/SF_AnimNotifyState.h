// ==================================================
// Filename	:	SF_AnimNotifyState.h
// Author	:	22cu0115 �≺��l
// Description: �v���C���[��AnimMontage�Őݒ肵��Nortify���Ăяo��
// Notes:		��
//				
// Update:		
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SF_AnimNotifyState.generated.h"

class UBoxComponent;
class ASF_WeaponBase;
class ASF_GameMode;
class ASF_Player;
     
UCLASS()
class SKYFLOWER_API USF_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
    USF_AnimNotifyState();

public:
    UPROPERTY(EditAnywhere)
        UBoxComponent* CollisionBoxComponent;
public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

public:
    ////////////////////////////////////////// Get�֐�
    FORCEINLINE ASF_GameMode* GetGameMode() const;

    FORCEINLINE ASF_Player* GetPlayerCharacter() const;
};
