// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_LockOnWidget.h"
#include "Components/WidgetComponent.h" 
#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"


// Sets default values
ASF_LockOnWidget::ASF_LockOnWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MyWidgetComponent"));
    WidgetComponent->SetupAttachment(RootComponent);
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawSize(FVector2D(256, 256));

    //static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/BP/UI/WBP_LockOn_UI"));
    //if (WidgetClass.Succeeded())
    //{
    //    WidgetComponent->SetWidgetClass(WidgetClass.Class);
    //}

}

// Called when the game starts or when spawned
void ASF_LockOnWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASF_LockOnWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

