// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Nightmare_Out_Trigger.h"
#include "WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget.h"


// Sets default values
ANightmare_Out_Trigger::ANightmare_Out_Trigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ANightmare_Out_Trigger::OnOverlapBegin);

}


// Called when the game starts or when spawned
void ANightmare_Out_Trigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANightmare_Out_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANightmare_Out_Trigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UWorld* World = GetWorld();

	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		if (World != nullptr && !DoOnce)
		{
			DoOnce = true;
			Character = Cast<AThe_VisionCharacter>(World->GetFirstPlayerController()->GetPawn());
			FTimerHandle TimeHandle;
			PlayerController = World->GetFirstPlayerController();
			PlayerController->GetPawn()->DisableInput(PlayerController);
			Character->ResetInputs();
			UWidgetLayoutLibrary::RemoveAllWidgets(World);
			UGameplayStatics::PlaySoundAtLocation(World, Nightmare_Sound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAttached(Nightmare_Blur_Back, Character->FirstPersonCamera);
			GetWorldTimerManager().SetTimer(TimeHandle, this, &ANightmare_Out_Trigger::Relocate_Player, 1.0f);
		}
	}
}


void ANightmare_Out_Trigger::Relocate_Player()
{
	Character->SetActorLocation(FVector(NewLocation_X, NewLocation_Y, NewLocation_Z));
	PlayerController->SetControlRotation(FRotator(NewRotation_X, NewRotation_Z, NewRotation_Y));
	PlayerController->GetPawn()->EnableInput(PlayerController);
	player_Interface = CreateWidget<UUserWidget>(GetWorld(), W_Interface);
	if (player_Interface)
	{
		player_Interface->AddToViewport();
	}

}

