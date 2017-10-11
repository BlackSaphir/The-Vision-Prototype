// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/The_VisionCharacter.h"
#include "Gameplay/Vision_Camera.h"
#include "The_Vision_Trigger.generated.h"

UCLASS()
class THE_VISION_API AThe_Vision_Trigger : public AActor
{
	GENERATED_BODY()

		AThe_Vision_Trigger();

	// Functions

private:
	void ChangePostProcess();
	void ChangeCamera();
	void Vision_Effets();
	void Backwards_Effets();
	void Change_Camera_Back();
	void AddInterface();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// Variables

private:
	AThe_VisionCharacter* character;
	APlayerController* playerController;
	AVision_Camera* vision_Camera;
	UWorld* world;
	TArray<AActor*>spawnPoint_Array;
	TArray<AActor*>Camera_Array;
	TArray<AActor*> Enemy_Array;
	TArray<UStaticMeshComponent*> Enemy_Mesh_Array;




public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class USoundBase* Vision_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Vision_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Vision_Particle_Back;

	UPROPERTY(EditAnywhere, Category = "The Vision")
		 FName CameraTag;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> W_Interface;

	bool DoOnce;


	// Components

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;

};
