// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "SlideDoor.h"


// Sets default values
ASlideDoor::ASlideDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SM_SlideDoor = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SlideDoorMesh"));
	SM_SlideDoor->SetAnimation(Anim_Forward_SlideDoor);

}

// Called when the game starts or when spawned
void ASlideDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASlideDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlideDoor::Activate()
{	
	if (!b_Open)
	{		
		SM_SlideDoor->SetPlayRate(1);
		SM_SlideDoor->Play(false);		
		b_Open = true;
	}
	else
	{	
		SM_SlideDoor->SetPlayRate(-1);
		SM_SlideDoor->Play(false);
		b_Open = false;
		
	}
}

