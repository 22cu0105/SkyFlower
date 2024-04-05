// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTActor.h"
#include "DebugHelpers.h"

// Sets default values
ATESTActor::ATESTActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATESTActor::BeginPlay()
{
	Super::BeginPlay();
	
	Debug::PrintFixedLine("BeginPlay");

	//DRAW_SPHERE(FVector(0,0,0))
	//DRAW_LINE(FVector(0, 0, 0), FVector(0, 0, 100))
}

// Called every frame
void ATESTActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Debug::PrintFixedLine("Tick   FixedLine     1",1);
	//Debug::PrintFixedLine("Tick   FixedLine     10",10);
	//Debug::Print("Tick");


}

