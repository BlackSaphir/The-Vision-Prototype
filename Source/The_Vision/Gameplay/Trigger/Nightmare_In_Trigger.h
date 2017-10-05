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

public:
	// Sets default values for this actor's properties
	ANightmare_In_Trigger();

	// Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "The Vision")
		class USoundBase* Vision_Sound;

	UPROPERTY(EditAnywhere, Category = "The Vision")
		class UParticleSystem* Vision_Blur;

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



	AThe_VisionCharacter* Character;



	//Component

public:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box;

	// Function

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "In_Trigger")
		void BBC();
};
