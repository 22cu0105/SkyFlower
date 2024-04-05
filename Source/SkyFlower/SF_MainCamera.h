// ==================================================
// Filename	:	SF_MainCamera.h
// Author	:	22cu0105 小田島 稜人
// Description:
// Update	:	2024/04/05
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_MainCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class ESF_CameraState : uint8
{
	None = 0			UMETA(DisplayName = "なし"),
	Normal				UMETA(DisplayName = "通常時"),
	NormalBattle		UMETA(DisplayName = "通常バトル時"),
	CloseBattle			UMETA(DisplayName = "近接バトル時"),
};

//USTRUCT(BlueprintType)
//struct FSF_CameraInfo
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	float Distance;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	float LerpSpeed;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	float FOV;
//
//public:
//	FSF_CameraInfo()
//		: Distance(500.f)
//		, LerpSpeed(1.f)
//		, FOV(1.f)
//	{}
//};

//------------------------------------------------------------------

UCLASS()
class SKYFLOWER_API ASF_MainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ASF_MainCamera();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void AddPitchRotation(float InValue);
	void AddYawRotation(float InValue);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	ESF_CameraState CameraState;

	UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	FVector ViewPoint;
	UPROPERTY(EditAnywhere, Category = "Camera | Edit")
	float MaxPitch;

public:
	ESF_CameraState GetCameraState() const { return CameraState; }
	FVector GetViewPoint() const { return ViewPoint; }
};
