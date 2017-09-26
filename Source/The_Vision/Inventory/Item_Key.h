// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActivationInterface.h"
#include "Item_Key.generated.h"

UCLASS()
class THE_VISION_API AItem_Key : public AActor, public IActivationInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem_Key();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate() override;

	int MagSize = 9;

	UPROPERTY(EditAnyWhere)
		class AThe_VisionCharacter* character;
};
