// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlasDoor_Doppel.generated.h"

UCLASS()
class THE_VISION_API AGlasDoor_Doppel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlasDoor_Doppel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void Open_Door();

	UFUNCTION(BlueprintImplementableEvent)
		void Close_Door();

	
	
};
