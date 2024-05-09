// ==================================================
// Filename	:	SF_FieldBase.h
// Author	:	22cu0105 ���c�� �Ől
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_FieldBase.generated.h"

/// @brief �t�B�[���h�̃C�x���g��Ԃ̗񋓌^
UENUM(/*BlueprintType*/)
enum class ESF_FieldEventType : uint8
{
	None = 0	UMETA(DisplayName = "�Ȃ�"),
	Waiting		UMETA(DisplayName = "�ҋ@��"),
	Active		UMETA(DisplayName = "������"),
	Inactive	UMETA(DisplayName = "�����I��"),
};

UCLASS()
class SKYFLOWER_API ASF_FieldBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASF_FieldBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UShapeComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere, Category = "FieldBase")
	ESF_FieldEventType FieldEventType;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "SF_StageDataModel"))
	FSoftObjectPath StageDataAsset;
};
