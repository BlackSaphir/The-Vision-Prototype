// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "The_Vision_Trigger.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AThe_Vision_Trigger::AThe_Vision_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThe_Vision_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThe_Vision_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThe_Vision_Trigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UWorld* World = GetWorld();

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (World != nullptr && !DoOnce)
		{
			TArray<AActor*> Camera_Array;

			character = Cast<AThe_VisionCharacter>(World->GetFirstPlayerController()->GetPawn());
			UGameplayStatics::GetAllActorsWithTag(World, FName("Vision_Trigger_Camera"), Camera_Array);

		}
	}
}

