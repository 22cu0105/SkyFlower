// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_MainCamera.h"

// Sets default values
ASF_MainCamera::ASF_MainCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASF_MainCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASF_MainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

