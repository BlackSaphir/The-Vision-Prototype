// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeginLevel_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UBeginLevel_Interface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class THE_VISION_API IBeginLevel_Interface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION()
		virtual void BeginLevel();

	UFUNCTION(BlueprintImplementableEvent, Category = "Level Start", meta = (DisplayName = "Begin Level"))
		void BPEvent_BeginLevel();
	
};
