// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VideoSettings_Widget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FConsoleVariableFinder
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video Settings")
		FName GraphicalQuality;
};

UCLASS()
class THE_VISION_API UVideoSettings_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	
	
	
};
