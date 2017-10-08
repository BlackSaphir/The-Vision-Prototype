// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/The_VisionCharacter.h"
#include "The_Vision_Trigger.generated.h"

UCLASS()
class THE_VISION_API AThe_Vision_Trigger : public AActor
{
	GENERATED_BODY()
	
	AThe_Vision_Trigger();

	// Functions

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	// Variables

private:
	AThe_VisionCharacter* character;
	UCameraComponent* Vision_Camera;


public:
	bool DoOnce;
};
