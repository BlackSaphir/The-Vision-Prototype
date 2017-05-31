// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/InputSettings.h"
#include "UMG.h"
#include "UMGStyle.h"
#include "Slate/SObjectWidget.h"
#include "IUMGModule.h"
#include "Blueprint/UserWidget.h"
#include "Settings_Widget.generated.h"

/**
 *
 */
UCLASS()
class THE_VISION_API USettings_Widget : public UUserWidget
{
	GENERATED_BODY()
//
//public:
//
//	UPROPERTY(BlueprintReadWrite)
//		UButton* Button;

public:

	UFUNCTION(BlueprintCallable, Category = "Nice")
		bool RemapActionKey(FInputActionKeyMapping newActionMapping);

	UFUNCTION(BlueprintPure, Category = "Very Nice")
		FText GetFireActionKeyName();
};
