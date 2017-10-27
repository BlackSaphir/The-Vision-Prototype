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
	FTimerHandle TimeHandle;

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
			UGameplayStatics::SpawnEmitterAttached(Vision_Particle, character->GetFirstPersonCameraComponent());
			GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::ChangePostProcess, 1.5f);

		}
	}
}

// Set Camera
void AThe_Vision_Trigger::ChangePostProcess()
{
	FTimerHandle TimeHandle;
	TSubclassOf<ASpawnPoint> SpawnPoint_tofind;
	SpawnPoint_tofind = ASpawnPoint::StaticClass();

	UGameplayStatics::GetAllActorsWithTag(world, CameraTag, Camera_Array);
	vision_Camera = Cast<AVision_Camera>(Camera_Array[0]);
	vision_Camera->The_Vision();
	UGameplayStatics::GetAllActorsOfClass(world, SpawnPoint_tofind, spawnPoint_Array);
	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::ChangeCamera, 1.0f);
}


// Spawn AI
void AThe_Vision_Trigger::ChangeCamera()
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
	playerController->SetViewTargetWithBlend(Camera_Array[0]);

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::Vision_Effets, 1.0f);
}



void AThe_Vision_Trigger::Vision_Effets()
{
	FTimerHandle TimeHandle;
	vision_Camera->InCamVision();
	vision_Camera->Play_Ambience_Camera_ViewChange();
	UGameplayStatics::GetAllActorsOfClass(world, TSubclassOf<AEnemy_Character>(), Enemy_Array);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		//Dieser Code erzeugt einen Penis in Les-Lees sandiger Vagina und ein Muffin
		Cast<AEnemy_Character>(Enemy_Array[i]);
		Enemy_Array[i]->GetComponents<UStaticMeshComponent>(Enemy_Mesh_Array);
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(true);
		Enemy_Mesh_Array[i]->SetCustomDepthStencilValue(254);
	}

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::Backwards_Effets, 10.0f);
}

void AThe_Vision_Trigger::Backwards_Effets()
{
	FTimerHandle TimeHandle;
	vision_Camera->Play_ChangeOut_Sound();
	vision_Camera->InCamBack();

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::Change_Camera_Back, 2.0f);
}

void AThe_Vision_Trigger::Change_Camera_Back()
{
	FTimerHandle TimeHandle;
	playerController->SetViewTargetWithBlend(playerController->GetPawn());
	vision_Camera->The_Vision_Backwards();
	UGameplayStatics::SpawnEmitterAttached(Vision_Particle_Back, character->FirstPersonCamera);
	for (int i = 0; i < Enemy_Array.Num(); i++)
	{
		Enemy_Mesh_Array[i]->SetRenderCustomDepth(false);
	}

	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_Vision_Trigger::AddInterface, 4.0f);
}

void AThe_Vision_Trigger::AddInterface()
{
	playerController->GetPawn()->EnableInput(playerController);
	UUserWidget* Interface = CreateWidget<UUserWidget>(world, W_Interface);
	if (Interface)
	{
		Interface->AddToViewport();
	}

}
