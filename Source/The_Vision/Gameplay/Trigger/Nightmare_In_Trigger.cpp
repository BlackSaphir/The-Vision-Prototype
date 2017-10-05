// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Nightmare_In_Trigger.h"
#include "WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UserWidget.h"



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
	UWorld* World = GetWorld();
	Character = Cast<AThe_VisionCharacter>(World->GetFirstPlayerController()->GetPawn());

	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		if (World != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("PENIS"));
			APlayerController* PlayerController = World->GetFirstPlayerController();
			PlayerController->GetPawn()->DisableInput(PlayerController);
			Character->ResetInputs();
			UWidgetLayoutLibrary::RemoveAllWidgets(World);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Vision_Sound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAttached(Vision_Blur, Character->FirstPersonCamera);
			UKismetSystemLibrary::Delay(World, 4.0f, FLatentActionInfo());
			Character->SetActorLocationAndRotation(FVector(NewLocation_X, NewLocation_Y, NewLocation_Z), FRotator(NewRotation_X, NewRotation_Y, NewRotation_Z));
			Vision_Blur->bAutoDeactivate = true;
			PlayerController->GetPawn()->EnableInput(PlayerController);		
			BBC();
		}

	}
}
