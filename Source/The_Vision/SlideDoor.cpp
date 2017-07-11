// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "SlideDoor.h"
#include "Kismet/GameplayStatics.h"


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

void ASlideDoor::ActivateInternal()
{	
	if (!b_Open)
	{		
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), Door_Open_Sound, ASlideDoor.GetLocation());
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

