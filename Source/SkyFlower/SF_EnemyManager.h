// ==================================================
// Filename	:	SF_EnemyManager.h
// Author	:	22cu0105 ���c�� �Ől
// Description: �G�𐶐����A�Ǘ�����R���|�[�l���g
// Update	:	2024/04/09
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EnemyManager.generated.h"

class ASF_EnemyBase;
class USF_EnemyGenerator;

// �G�̐������@�̗񋓌^
UENUM(BlueprintType)
enum class ESF_SpawnType : uint8
{
	None = 0		UMETA(DisplayName = "�Ȃ�"),
	Normal			UMETA(DisplayName = "�ʏ�G"),
	FlockEnemy		UMETA(DisplayName = "�G�Q��"),
};

//--------------------------------------------------------------------------------------------

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYFLOWER_API USF_EnemyManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USF_EnemyManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// �G�̐������@����GAI�𐶐�����֐����ꍇ��������
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	void SpawnAIEnemyFromGenerationType(const ESF_SpawnType InSpawnType, const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemy, const int InNum = 1);

	// �����̍��W�Ɉ�ԋ߂��G�̍��W���擾
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	FVector GetNearestEnemyPos(const FVector& InLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyManager", meta = (AllowPrivateAccess = "true"))
	USF_EnemyGenerator* EnemyGenerator;

	// �G���Ǘ�����z��
	UPROPERTY()
	TArray<ASF_EnemyBase*> EnemyList;

public:
	// ���ݐ����Ă���G�̐����擾
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	int GetCurrentEnemyNum() const { return EnemyList.Num(); }

private:
	// �Ǘ����Ă���G�����S���Ă��邩���肵�A����ł�����Ǘ��̈���������
	TArray<ASF_EnemyBase*> TryGetDeadEnemies() const;

	void NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
	void FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
};
