// ==================================================
// Filename	:	SF_EnemyManager.h
// Author	:	22cu0105 ¬“c“‡ —Ål
// Description: “G‚ğ¶¬‚µAŠÇ—‚·‚éƒRƒ“ƒ|[ƒlƒ“ƒg
// Update	:	2024/04/09
// ==================================================
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SF_EnemyManager.generated.h"

class ASF_EnemyBase;
class USF_EnemyGenerator;

// “G‚Ì¶¬•û–@‚Ì—ñ‹“Œ^
UENUM(BlueprintType)
enum class ESF_SpawnType : uint8
{
	None = 0		UMETA(DisplayName = "‚È‚µ"),
	Normal			UMETA(DisplayName = "’Êí“G"),
	FlockEnemy		UMETA(DisplayName = "“GŒQ‘Ì"),
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

	// “G‚Ì¶¬•û–@‚©‚ç“GAI‚ğ¶¬‚·‚éŠÖ”‚ğê‡•ª‚¯‚·‚é
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	void SpawnAIEnemyFromGenerationType(const ESF_SpawnType InSpawnType, const FVector& InLocation, TSubclassOf<ASF_EnemyBase> const InEnemy, const int InNum = 1);

	// ˆø”‚ÌÀ•W‚Éˆê”Ô‹ß‚¢“G‚ÌÀ•W‚ğæ“¾
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	FVector GetNearestEnemyPos(const FVector& InLocation);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnemyManager", meta = (AllowPrivateAccess = "true"))
	USF_EnemyGenerator* EnemyGenerator;

	// “G‚ğŠÇ—‚·‚é”z—ñ
	UPROPERTY()
	TArray<ASF_EnemyBase*> EnemyList;

public:
	// Œ»İ¶‚«‚Ä‚¢‚é“G‚Ì”‚ğæ“¾
	UFUNCTION(BlueprintCallable, Category = "EnemyManager")
	int GetCurrentEnemyNum() const { return EnemyList.Num(); }

private:
	// ŠÇ—‚µ‚Ä‚¢‚é“G‚ª€–S‚µ‚Ä‚¢‚é‚©”»’è‚µA€‚ñ‚Å‚¢‚½‚çŠÇ——Ìˆæ‚ğ‰ğ•ú‚·‚é
	TArray<ASF_EnemyBase*> TryGetDeadEnemies() const;

	void NormalAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
	void FlockAIEnemySpawn(TSubclassOf<ASF_EnemyBase> const InEnemy, const FVector& InLocation, const int InNum = 1);
};
