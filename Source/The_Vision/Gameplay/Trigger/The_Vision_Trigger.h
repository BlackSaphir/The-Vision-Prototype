// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/The_VisionCharacter.h"
#include "GlasDoor_Doppel.h"
#include "Gameplay/Vision_Post_Process.h"
#include "AI/Enemy_Character.h"
#include "The_Vision_Trigger.generated.h"

UCLASS()
class THE_VISION_API AThe_Vision_Trigger : public AActor
{
	GENERATED_BODY()

		AThe_Vision_Trigger();

	// Functions

private:
	void ChangePostProcess();
	void spawn_Enemy();
	void Vision_Effets();
	void GetEnemy();
	void relocated_Player();


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
	AEnemy_Character* enemy_Character;
	UWorld* world;
	AVision_Post_Process* Chameleon;
	TArray<AActor*>chameleon_Array;
	TArray<AActor*>spawnPoint_Array;
	TArray<AActor*> Enemy_Array;
	TArray<UStaticMeshComponent*> Enemy_Mesh_Array;
	TArray<AActor*> to_be_closed_Array;
	TArray<AActor*> to_be_opened_Array;
	AGlasDoor_Doppel* to_be_opened_Door;
	AGlasDoor_Doppel* to_be_closed_Door;
	bool DoOnce;




public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class USoundBase* Vision_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Vision_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Vision_Particle_Back;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> W_Interface;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_X;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_Y;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_Z;


	// Components

private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;

};
