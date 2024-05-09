// ==================================================
// Filename	:	SF_LockOnWidget.h
// Author	:	22cu0214 JinWener
// Description:	Display LockOn icon on target enemy position
// Notes:		
// Update:		2024/05/08 22cu0214 init 
// ==================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UMG.h" 
#include "SF_LockOnWidget.generated.h"

class UWidgetComponent;


UCLASS()
class SKYFLOWER_API ASF_LockOnWidget : public AActor
{
	GENERATED_BODY()

	////////////////////// override function
public:
	ASF_LockOnWidget();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	////////////////////// custom function
	////////////////////// BlueprintImplementableEvent
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetIconVisibility(ESlateVisibility visibility);

	UFUNCTION(BlueprintImplementableEvent)
	void SetActorVisible(bool isVisible);

	////////////////////// custom variable
protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;
};
