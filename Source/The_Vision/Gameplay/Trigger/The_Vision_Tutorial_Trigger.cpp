// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "The_Vision_Tutorial_Trigger.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetLayoutLibrary.h"
#include "AI/SpawnPoint_Tutorial.h"
#include "AI/Enemy_Character.h"
#include "UserWidget.h"


// Sets default values
AThe_Vision_Tutorial_Trigger::AThe_Vision_Tutorial_Trigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	Box->OnComponentBeginOverlap.AddDynamic(this, &AThe_Vision_Tutorial_Trigger::OnOverlapBegin);

}



// Called when the game starts or when spawned
void AThe_Vision_Tutorial_Trigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThe_Vision_Tutorial_Trigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThe_Vision_Tutorial_Trigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	world = GetWorld();

	if ((OtherActor != nullptr) && ( OtherComp != nullptr) && (OtherActor != this))
	{
		if (world != nullptr && !DoOnce)
		{
			DoOnce = true;
			playerController = world->GetFirstPlayerController();
			character = Cast<AThe_VisionCharacter>(playerController->GetPawn());

			character->DisableInput(playerController);
			character->ResetInputs();
			UWidgetLayoutLibrary::RemoveAllWidgets(world);
			UGameplayStatics::PlaySoundAtLocation(world, Vision_Sound, GetActorLocation());
			//UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
			ChangePostProcess();
		}
	}
}


void AThe_Vision_Tutorial_Trigger::ChangePostProcess()
{
	TSubclassOf<ASpawnPoint_Tutorial> SpawnPoint_tofind;
	SpawnPoint_tofind = ASpawnPoint_Tutorial::StaticClass();

	UGameplayStatics::GetAllActorsWithTag(world, FName("Tutorial_Slide_Door_Close"), to_be_closed_Array);
	to_be_closed_Door = Cast<ASlideDoor>(to_be_closed_Array[0]);
	UGameplayStatics::GetAllActorsWithTag(world, FName("Tutorial_Slide_Door_Open"), to_be_opened_Array);
	to_be_opened_Door = Cast<ASlideDoor>(to_be_opened_Array[0]);

	UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
	to_be_closed_Door->Close_Door();
	to_be_opened_Door->Open_Door();
	character->EnableInput(playerController);
	UGameplayStatics::GetAllActorsOfClass(world, SpawnPoint_tofind, spawnPoint_Array);
	Spawn_Enemy();
}

void AThe_Vision_Tutorial_Trigger::Spawn_Enemy()
{
	if (spawnPoint_Array[0]->IsA(ASpawnPoint_Tutorial::StaticClass()))
	{
		for (int i = 0; i < spawnPoint_Array.Num(); i++)
		{
			if (spawnPoint_Array[i]->IsA(ASpawnPoint_Tutorial::StaticClass()))
			{
				Cast<ASpawnPoint_Tutorial>(spawnPoint_Array[i])->SetSpawnBoolTrue_Tutorial();
			}
		}
	}
	FTimerHandle TimeHandle;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Tutorial_Trigger::Relocated_Player, 11.0f);
	Vision_Effets();
}

void AThe_Vision_Tutorial_Trigger::Vision_Effets()
{
	TSubclassOf<AVision_Post_Process> Chameleon_tofind;
	Chameleon_tofind = AVision_Post_Process::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(world, Chameleon_tofind, chameleon_Array);
	Chameleon = Cast<AVision_Post_Process>(chameleon_Array[0]);
	Chameleon->Start_Vision();


	UGameplayStatics::GetAllActorsOfClass(world, TSubclassOf<AEnemy_Character>(), Enemy_Array);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		Cast<AEnemy_Character>(Enemy_Array[i]);
		Enemy_Array[i]->GetComponents<UStaticMeshComponent>(Enemy_Mesh_Array);
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(true);
		Enemy_Mesh_Array[i]->SetCustomDepthStencilValue(254);
	}
}

void AThe_Vision_Tutorial_Trigger::Relocated_Player()
{
	UGameplayStatics::SpawnEmitterAttached(Vision_Particle_Back, character->GetFirstPersonCameraComponent());
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

