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
			UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::ChangePostProcess, 1.5f);
		}
	}
}


void AThe_Vision_Tutorial_Trigger::ChangePostProcess()
{
	FTimerHandle TimerHandle;
	TSubclassOf<ASpawnPoint_Tutorial> SpawnPoint_tofind;
	SpawnPoint_tofind = ASpawnPoint_Tutorial::StaticClass();

	UGameplayStatics::GetAllActorsWithTag(world, CameraTag, Camera_Array);
	vision_Camera = Cast<AVision_Camera_Tutorial>(Camera_Array[0]);
	vision_Camera->The_Vision();
	UGameplayStatics::GetAllActorsOfClass(world, SpawnPoint_tofind, spawnPoint_Array);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::ChangeCamera, 1.0f);
}

void AThe_Vision_Tutorial_Trigger::ChangeCamera()
{
	FTimerHandle TimerHandle;
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

	playerController->SetViewTargetWithBlend(Camera_Array[0]);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::Vision_Effets, 1.0f);
}

void AThe_Vision_Tutorial_Trigger::Vision_Effets()
{
	vision_Camera->InCamVision();
	vision_Camera->Play_Ambience_Camera_ViewChange();
	UGameplayStatics::GetAllActorsOfClass(world, TSubclassOf<AEnemy_Character>(), Enemy_Array);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		Cast<AEnemy_Character>(Enemy_Array[i]);
		Enemy_Array[i]->GetComponents<UStaticMeshComponent>(Enemy_Mesh_Array);
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(true);
		Enemy_Mesh_Array[i]->SetCustomDepthStencilValue(254);
	}
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::Backwards_Effets, 10.0f);
}

void AThe_Vision_Tutorial_Trigger::Backwards_Effets()
{
	FTimerHandle TimerHandle;
	vision_Camera->Play_ChangeOut_Sound();
	vision_Camera->InCamBack();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::Change_Camera_Back, 0.5f);
}

void AThe_Vision_Tutorial_Trigger::Change_Camera_Back()
{
	FTimerHandle TimerHandle;
	playerController->SetViewTargetWithBlend(playerController->GetPawn());
	vision_Camera->The_Vision_Backwards();
	UGameplayStatics::SpawnEmitterAttached(Vision_Particle_Back, character->GetFirstPersonCameraComponent());
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(false);
	}
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AThe_Vision_Tutorial_Trigger::AddInterface, 4.0f);
}

void AThe_Vision_Tutorial_Trigger::AddInterface()
{
	playerController->GetPawn()->EnableInput(playerController);
	UUserWidget* Interface = CreateWidget<UUserWidget>(world, W_Interface);
	if (Interface)
	{
		Interface->AddToViewport();
	}
}

