// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Settings_Widget.h"

FInputActionKeyMapping FVisionInputActionKeyMapping::Convert(FVisionInputActionKeyMapping const & VisionInputActionKeyMapping)
{
	return FInputActionKeyMapping() =
	{ 
		VisionInputActionKeyMapping.ActionName ,
		VisionInputActionKeyMapping.Key,
		VisionInputActionKeyMapping.bShift,
		VisionInputActionKeyMapping.bCtrl ,
		VisionInputActionKeyMapping.bAlt,
		VisionInputActionKeyMapping.bCmd 
	};
}

bool USettings_Widget::RemapActionKey(const FInputActionKeyMapping& newActionMapping)
{
	if (UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>()))
	{
		TArray< FInputActionKeyMapping>& Actions = InputSettings->ActionMappings;

		bool bFound = false;
		for (auto& Action : Actions)
		{
			if (Action.ActionName == newActionMapping.ActionName)
			{
				Action = newActionMapping;
				bFound = true;
				break;
			}
		}

		if (bFound)
		{
			// SAVE NEW SETTINGS TO CONFIG FILE ON DISK
			InputSettings->SaveKeyMappings();

			// creates modified config in Saved/Config/Windows/Input.ini
			// Updates game with newn input
			for (TObjectIterator<UPlayerInput> Iter; Iter; ++Iter)
			{
				Iter->ForceRebuildingKeyMaps(true);
			}
		}
		return bFound;
	}
	else
	{
		return false;
	}
}

FText USettings_Widget::GetFireActionKeyName()
{
	return GetActionKeyName(TEXT("Fire"));
}

FText USettings_Widget::GetTestActionKeyName()
{
	return GetActionKeyName(TEXT("Test"));
}

FText USettings_Widget::GetActionKeyName(FName const& ActionName)
{
	if (UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>()))
	{
		TArray< FInputActionKeyMapping>& Actions = InputSettings->ActionMappings;

		for (auto& Action : Actions)
		{
			if (Action.ActionName == ActionName)
			{
				return Action.Key.GetDisplayName();
			}
		}
	}

	return FText::FromString("Penis");
}
