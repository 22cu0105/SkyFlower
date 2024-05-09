// ==================================================
// Filename	:	SF_FieldBase.h
// Author	:	22cu0105 小田島 稜人
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_FieldBase.generated.h"

/// @brief フィールドのイベント状態の列挙型
UENUM(/*BlueprintType*/)
enum class ESF_FieldEventType : uint8
{
	None = 0	UMETA(DisplayName = "なし"),
	Waiting		UMETA(DisplayName = "待機中"),
	Active		UMETA(DisplayName = "処理中"),
	Inactive	UMETA(DisplayName = "処理終了"),
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
