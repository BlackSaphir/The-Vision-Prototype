// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Audio_Widget.h"


float UAudio_Widget::VictoryGetSoundVolume(USoundClass* SoundClassObject)
{
	if (!SoundClassObject)
	{
		return -1;
	}
	return SoundClassObject->Properties.Volume;
}

bool UAudio_Widget::VictorySoundVolumeChange(USoundClass* SoundClassObject, float NewVolume)
{
	if (!SoundClassObject)
	{
		return false;
	}

	SoundClassObject->Properties.Volume = NewVolume;
	return true;
}

