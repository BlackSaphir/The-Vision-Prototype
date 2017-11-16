// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "The_Vision_Trigger.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetLayoutLibrary.h"
#include "AI/SpawnPoint.h"
#include "AI/Enemy_Character.h"
#include "UserWidget.h"


// Sets default values
AThe_Vision_Trigger::AThe_Vision_Trigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	Box->OnComponentBeginOverlap.AddDynamic(this, &AThe_Vision_Trigger::OnOverlapBegin);
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


// OnOverlap spawn Sound & Emitter
void AThe_Vision_Trigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	world = GetWorld();
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (world != nullptr && !DoOnce)
		{
			DoOnce = true;
			playerController = GetWorld()->GetFirstPlayerController();
			character = Cast<AThe_VisionCharacter>(playerController->GetPawn());

			playerController->GetPawn()->DisableInput(world->GetFirstPlayerController());
			character->ResetInputs();
			UWidgetLayoutLibrary::RemoveAllWidgets(world);
			UGameplayStatics::PlaySoundAtLocation(world, Vision_Sound, GetActorLocation());
			//UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
			ChangePostProcess();
		}
	}
}

// Set Camera
void AThe_Vision_Trigger::ChangePostProcess()
{
	TSubclassOf<ASpawnPoint> SpawnPoint_tofind;
	SpawnPoint_tofind = ASpawnPoint::StaticClass();

	UGameplayStatics::GetAllActorsWithTag(world, FName("Vision_Glas_Door_Close"), to_be_closed_Array);
	to_be_closed_Door = Cast<AGlasDoor_Doppel>(to_be_closed_Array[0]);
	UGameplayStatics::GetAllActorsWithTag(world, FName("Vision_Glas_Door_Open"), to_be_opened_Array);
	to_be_opened_Door = Cast<AGlasDoor_Doppel>(to_be_opened_Array[0]);

	UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
	to_be_closed_Door->Close_Door();
	to_be_opened_Door->Open_Door();
	character->EnableInput(playerController);

	UGameplayStatics::GetAllActorsOfClass(world, SpawnPoint_tofind, spawnPoint_Array);
	spawn_Enemy();
}


// Spawn AI
void AThe_Vision_Trigger::spawn_Enemy()
{
	FTimerHandle TimeHandle;
	if (spawnPoint_Array[0]->IsA(ASpawnPoint::StaticClass()))
	{
		for (int i = 0; i < spawnPoint_Array.Num(); i++)
		{
			if (spawnPoint_Array[i]->IsA(ASpawnPoint::StaticClass()))
			{
				Cast<ASpawnPoint>(spawnPoint_Array[i])->SetSpawnBoolTrue();
			}
		}
	}

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::relocated_Player, 11.0f);
	Vision_Effets();
}



void AThe_Vision_Trigger::Vision_Effets()
{
	TSubclassOf<AVision_Post_Process> Chameleon_tofind;
	Chameleon_tofind = AVision_Post_Process::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(world, Chameleon_tofind, chameleon_Array);
	Chameleon = Cast <AVision_Post_Process>(chameleon_Array[0]);
	Chameleon->Start_Vision();



	UGameplayStatics::GetAllActorsOfClass(world, TSubclassOf<AEnemy_Character>(), Enemy_Array);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		//Dieser Code erzeugt einen Penis in Les-Lees sandiger Vagina und ein Muffin
		Cast<AEnemy_Character>(Enemy_Array[i]);
		Enemy_Array[i]->GetComponents<UStaticMeshComponent>(Enemy_Mesh_Array);
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(true);
		Enemy_Mesh_Array[i]->SetCustomDepthStencilValue(254);
	}
}

void AThe_Vision_Trigger::relocated_Player()
{
	UGameplayStatics::SpawnEmitterAttached(Vision_Particle_Back, character->FirstPersonCamera);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(false);
	}

	character->DisableInput(playerController);
	character->ResetInputs();
	to_be_closed_Door->Open_Door();
	to_be_opened_Door->Close_Door();
	character->SetActorLocation(this->GetActorLocation());
	playerController->SetControlRotation(FRotator(NewRotation_X, NewRotation_Z, NewRotation_Y));
	Chameleon->End_Vision();

	UUserWidget* Interface = CreateWidget<UUserWidget>(world, W_Interface);
	if (Interface)
	{
		Interface->AddToViewport();
	}
	playerController->GetPawn()->EnableInput(playerController);

}
