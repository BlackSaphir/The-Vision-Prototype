// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Nightmare_In_Trigger.h"


// Sets default values
ANightmare_In_Trigger::ANightmare_In_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANightmare_In_Trigger::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ANightmare_In_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANightmare_In_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANightmare_In_Trigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		if (GetWorld() != nullptr)
		{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		AActor::DisableInput(PlayerController);
			
		}
	}
}

