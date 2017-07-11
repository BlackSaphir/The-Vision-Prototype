// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActivationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UActivationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 *
 */
class THE_VISION_API IActivationInterface
{
	GENERATED_IINTERFACE_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
		virtual	void Activate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Penis")
		void BPEvent_Activate();
};
