// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SpawnPoint.h"
#include "SpawnPoint_Tutorial.generated.h"

/**
 * 
 */
UCLASS()
class THE_VISION_API ASpawnPoint_Tutorial : public ASpawnPoint
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	ASpawnPoint_Tutorial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		 void SetSpawnBoolTrue_Tutorial();
};
