// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vision_Post_Process.generated.h"

UCLASS()
class THE_VISION_API AVision_Post_Process : public AActor
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	AVision_Post_Process();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Variable

	UFUNCTION(BlueprintImplementableEvent)
		void Start_Vision();

	UFUNCTION(BlueprintImplementableEvent)
		void End_Vision();
	
};
