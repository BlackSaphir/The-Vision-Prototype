// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/The_VisionCharacter.h"
#include "Nightmare_In_Trigger.generated.h"

UCLASS()
class THE_VISION_API ANightmare_In_Trigger : public AActor
{
	GENERATED_BODY()

	// Sets default values for this actor's properties
	ANightmare_In_Trigger();

	// Variables

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class USoundBase* Nightmare_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Nightmare_Blur;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class UParticleSystem* Nightmare_Blur_Back;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewLocation_X;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewLocation_Y;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewLocation_Z;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_X;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_Y;

	UPROPERTY(EditAnywhere, Category = "Transform")
		float NewRotation_Z;

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> W_Interface;

	AThe_VisionCharacter* Character;

	bool DoOnce = false;

private:

	UUserWidget* player_Interface;
	APawn * Player_Pawn;


	//Component

public:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;

	// Function

private:

	void Relocate_Player();
	void Add_Interface();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};