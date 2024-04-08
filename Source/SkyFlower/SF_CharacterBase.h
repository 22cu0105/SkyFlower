// ==================================================
// Filename	:	SF_CharacterBace.h
// Author	:	22cu0105 ���c�� �Ől
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

UENUM(BlueprintType)
enum class ESF_CharacterState : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Normal				UMETA(DisplayName = "�ʏ펞"),
	BeginAttack			UMETA(DisplayName = "�U���J�n��"),
	ShortRangeAttack	UMETA(DisplayName = "�ߋ����U��"),
	LongRangeAttack		UMETA(DisplayName = "�������U��"),
	EndAttack			UMETA(DisplayName = "�U���I����"),
};


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
	UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	ASF_WeaponBase* WeaponActor;
	UPROPERTY(VisibleAnywhere, Category = "Visible | Equipment")
	ASF_Shield* ShieldActor;

	UPROPERTY(VisibleAnywhere, Category = "Visible | CharacterState")
	ESF_CharacterState CharacterState;

public:
	ASF_WeaponBase* GetWeaponActor() const { return WeaponActor; }
	ASF_Shield* GetShieldActor() const { return ShieldActor; }

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void SetCharacterState(const ESF_CharacterState InCharacterState) { CharacterState = InCharacterState; }
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	ESF_CharacterState GetCharacterState() { return CharacterState; }
};