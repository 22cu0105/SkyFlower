// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0105 è¨ìcìá ó≈êl
// Description:
// Update	:	2024/04/05
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SF_CharacterBase.generated.h"

class ASF_EquipmentBase;

UCLASS()
class SKYFLOWER_API ASF_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASF_CharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Equip(ASF_EquipmentBase* const InEquipment, const FName& InSoketName);
};