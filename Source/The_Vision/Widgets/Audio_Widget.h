// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Audio_Widget.generated.h"

/**
 *
 */
UCLASS()
class THE_VISION_API UAudio_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Victory BP Library|Sound")
		static float VictoryGetSoundVolume(USoundClass* SoundClassObject);

	UFUNCTION(BlueprintCallable, Category = "Victory BP Library|Sound")
		static bool VictorySoundVolumeChange(USoundClass* SoundClassObject, float NewVolume);

};
