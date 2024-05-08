#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SF_StageInfo.h"
#include "SF_StageDataModel.generated.h"

class UDataTable;

UCLASS()
class SKYFLOWER_API USF_StageDataModel : public UDataAsset
{
	GENERATED_BODY()

public:

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* StageDataTable;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<uint8, FSF_StageInfo> StageDataMap;

public:
	UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true"))
	void LoadData();
};
