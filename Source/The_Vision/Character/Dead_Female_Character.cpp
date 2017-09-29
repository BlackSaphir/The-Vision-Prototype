// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Dead_Female_Character.h"


// Sets default values
ADead_Female_Character::ADead_Female_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADead_Female_Character::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
}

// Called every frame
void ADead_Female_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADead_Female_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

