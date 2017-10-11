// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "Vision_Camera.generated.h"

/**
 * 
 */
UCLASS()
class THE_VISION_API AVision_Camera : public ACameraActor
{
	GENERATED_BODY()

		AVision_Camera();
	
	// Function

public:

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
		void The_Vision();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void The_Vision_Backwards();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void InCamVision();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void InCamBack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Play_Ambience_Camera_ViewChange();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Play_ChangeOut_Sound();

protected:

	virtual void BeginPlay() override;



	// Variables

	UPROPERTY(EditAnywhere, Category = "The Vision")
		FName CameraTag;
	
	
};
