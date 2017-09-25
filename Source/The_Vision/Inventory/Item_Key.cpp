// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Item_Key.h"


// Sets default values
AItem_Key::AItem_Key()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem_Key::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_Key::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_Key::Activate()
{
	Destroy(true);
}

