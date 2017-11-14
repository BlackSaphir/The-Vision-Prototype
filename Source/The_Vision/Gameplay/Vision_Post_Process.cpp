// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Vision_Post_Process.h"


// Sets default values
AVision_Post_Process::AVision_Post_Process()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVision_Post_Process::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVision_Post_Process::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

