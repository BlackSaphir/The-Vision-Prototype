// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActivationInterface.h"
#include "GameFramework/Actor.h"
#include "SlideDoor.generated.h"

UCLASS()
class THE_VISION_API ASlideDoor : public AActor, public IActivationInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* SM_SlideDoor;

	UPROPERTY(EditAnywhere, Category = Mesh)
		UAnimationAsset* Anim_Forward_SlideDoor;	

	bool b_Open = false;

public:
	// Sets default values for this actor's properties
	ASlideDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Activate();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
