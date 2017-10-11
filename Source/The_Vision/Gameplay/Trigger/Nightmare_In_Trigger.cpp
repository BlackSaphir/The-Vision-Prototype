// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Nightmare_In_Trigger.h"
#include "WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
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



	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		if (World != nullptr && !DoOnce)
		{
			DoOnce = true;
			Character = Cast<AThe_VisionCharacter>(World->GetFirstPlayerController()->GetPawn());
			FTimerHandle TimeHandle;
			PlayerController = World->GetFirstPlayerController();
			Player_Pawn = PlayerController->GetPawn();
			UE_LOG(LogTemp, Warning, TEXT("PENIS"));
			PlayerController->GetPawn()->DisableInput(PlayerController);
			Player_Pawn->DisableInput(PlayerController);
			Character->ResetInputs();
			UWidgetLayoutLibrary::RemoveAllWidgets(World);
			UGameplayStatics::PlaySoundAtLocation(World, Nightmare_Sound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAttached(Nightmare_Blur, Character->FirstPersonCamera);
			GetWorldTimerManager().SetTimer(TimeHandle, this, &ANightmare_In_Trigger::Relocate_Player, 4.0f);
		}

	}
}

void ANightmare_In_Trigger::Relocate_Player()
{
	FTimerHandle TimeHandle;

	Character->SetActorLocation(FVector(NewLocation_X, NewLocation_Y, NewLocation_Z));
	PlayerController->SetControlRotation(FRotator(NewRotation_X, NewRotation_Z, NewRotation_Y));
	UGameplayStatics::SpawnEmitterAttached(Nightmare_Blur_Back, Character->FirstPersonCamera);
	Nightmare_Blur->bAutoDeactivate = true;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &ANightmare_In_Trigger::Add_Interface, 4.0f);

}

void ANightmare_In_Trigger::Add_Interface()
{
	Player_Pawn->EnableInput(PlayerController);
	player_Interface = CreateWidget<UUserWidget>(GetWorld(), W_Interface);
	if (player_Interface)
	{
		player_Interface->AddToViewport();
	}
	Nightmare_Blur_Back->bAutoDeactivate = true;
}
