// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CharacterBase.h"

// Sets default values
ASF_CharacterBase::ASF_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASF_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASF_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASF_CharacterBase::Equip(ASF_EquipmentBase* const InEquipment, const FName& InSoketName)
{

}