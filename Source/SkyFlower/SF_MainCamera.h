// ==================================================
// Filename	:	SF_MainCamera.h
// Author	:	22cu0105 ���c�� �Ől
// Description:
// Update	:	2024/04/05
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SF_MainCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

/// @brief �J�����X�e�[�g�̗񋓌^
UENUM(BlueprintType)
enum class ESF_CameraState : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Normal				UMETA(DisplayName = "�ʏ펞"),
	NormalBattle		UMETA(DisplayName = "�ʏ�o�g����"),
	CloseBattle			UMETA(DisplayName = "�ߐڃo�g����"),
};

/// @brief �C�x���g���̏�����Map�ŊǗ����邽�߂̗񋓌^
UENUM(BlueprintType)
enum class ESF_CameraEventType : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Dash				UMETA(DisplayName = "�_�b�V����"),
};

/// @brief �l�̕ω���Ԃ�Map�ŊǗ����邽�߂̗񋓌^
UENUM(BlueprintType)
enum class ESF_AddValueMode : uint8
{
	None = 0			UMETA(DisplayName = "�Ȃ�"),
	Add					UMETA(DisplayName = "���@"),
	Reduce				UMETA(DisplayName = "���@"),
};

/// @brief �l�������@�ŕω�������\����
USTRUCT(BlueprintType)
struct FSF_ChangeValueInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxOrMinValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AddValue;

public:
	FSF_ChangeValueInfo()
		: MaxOrMinValue(0.f)
		, AddValue(0.f)
		, CurrentValue(0.f)
	{}
};

/// @brief Map��Map���Ǘ����邽�߂̍\����
USTRUCT(BlueprintType)
struct FSF_CameraInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESF_AddValueMode CurrentMode;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ESF_AddValueMode, FSF_ChangeValueInfo> InfoMap;

public:
	FSF_CameraInfo()
		: CurrentMode(ESF_AddValueMode::None)
		, InfoMap()
	{}
};

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

	UPROPERTY(VisibleAnywhere, Category = "Camera | Visible")
	ESF_CameraEventType CurrentCameraEventType;

	UPROPERTY(EditAnywhere, Category = "Camera | Edit")
	TMap<ESF_CameraEventType, FSF_CameraInfo> FOVInfoMap;

public:
	ESF_CameraState GetCameraState() const { return CameraState; }
	FVector GetViewPoint() const { return ViewPoint; }
};
