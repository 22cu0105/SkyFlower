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
class ASF_WeaponBase;
class ASF_Shield;

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
	void EquipWeapon(ASF_WeaponBase* const InWeapon, const FName& InSoketName);
	void EquipShield(ASF_Shield* const InShield, const FName& InSoketName);

private:
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	ASF_WeaponBase* WeaponActor;
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	ASF_Shield* ShieldActor;

public:
	ASF_WeaponBase* GetWeaponActor() const { return WeaponActor; }
	ASF_Shield* GetShieldActor() const { return ShieldActor; }
};