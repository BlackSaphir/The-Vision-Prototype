// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Inventory_Manager.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
AInventory_Manager::AInventory_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventory_Manager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventory_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventory_Manager::AddItemtoList(AActor* Item)
{
	Items.Add(Item);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Added Item to Array"));
}

