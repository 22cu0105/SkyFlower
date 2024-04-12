// ==================================================
// Filename	:	SF_EnemyBase.h
// Author	:	22cu0115 �≺��l
// Description: �G�l�~�[�̊��N���X
// Notes:		��
//				
// Update:		2024/04/12 22cu0115 
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "SF_CharacterBase.h"
#include "SF_EnemyBase.generated.h"

class UPawnSensingComponent;
class UBoxComponent;

UCLASS()
class SKYFLOWER_API ASF_EnemyBase : public ASF_CharacterBase
{
	GENERATED_BODY()

public:
	ASF_EnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// �R���W����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* CollisionBox;

public:
	// �I�[�o�[���b�v�C�x���g
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
