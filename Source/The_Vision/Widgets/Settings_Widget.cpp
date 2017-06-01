// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Settings_Widget.h"

// Set Mapping new
FInputActionKeyMapping FVisionInputActionKeyMapping::ConvertActionMapping(FVisionInputActionKeyMapping const & VisionInputActionKeyMapping)
{
	FInputActionKeyMapping ActionMapping;
	ActionMapping.ActionName = VisionInputActionKeyMapping.ActionName;
	ActionMapping.Key = VisionInputActionKeyMapping.Key;
	ActionMapping.bShift = VisionInputActionKeyMapping.bShift;
	ActionMapping.bCtrl = VisionInputActionKeyMapping.bCtrl;
	ActionMapping.bAlt = VisionInputActionKeyMapping.bAlt;
	ActionMapping.bCmd = VisionInputActionKeyMapping.bCmd;
	return ActionMapping;
}

FInputAxisKeyMapping FVisionInputAxisKeyMapping::ConvertAxisMapping(FVisionInputAxisKeyMapping const & VisionInputAxisKeyMapping)
{
	FInputAxisKeyMapping AxisMapping;
	AxisMapping.AxisName = VisionInputAxisKeyMapping.AxisName;
	AxisMapping.Key = VisionInputAxisKeyMapping.Key;
	AxisMapping.Scale = VisionInputAxisKeyMapping.Scale;
	
	return AxisMapping;
}



bool USettings_Widget::RemapActionKey(const FVisionInputActionKeyMapping& newActionMapping)
{
	if (UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>()))
	{
		TArray< FInputActionKeyMapping>& Actions = InputSettings->ActionMappings;

		bool bFound = false;
		for (auto& Action : Actions)
		{ 
			if (Action.ActionName == newActionMapping.ActionName)
			{
				Action = FVisionInputActionKeyMapping::ConvertActionMapping(newActionMapping);
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


bool USettings_Widget::RemapAxisKey(const FInputAxisKeyMapping & newAxisMapping)
{
	if (UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>()))
	{
		TArray< FInputAxisKeyMapping>& AxisKeys = InputSettings->AxisMappings;

		bool bFound = false;
		for (auto& AxisKey : AxisKeys)
		{
			if (AxisKey == newAxisMapping.AxisName)
			{
				AxisKey = FVisionInputAxisKeyMapping::ConvertAxisMapping(newAxisMapping);
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

FText USettings_Widget::GetZoomActionKeyName()
{
	return GetActionKeyName(TEXT("Zoom"));
}

FText USettings_Widget::GetReloadActionKeyName()
{
	return GetActionKeyName(TEXT("Reload"));
}

FText USettings_Widget::GetInteractActionKeyName()
{
	return GetActionKeyName(TEXT("Interact"));
}

FText USettings_Widget::GetOpenInventoryActionKeyName()
{
	return GetActionKeyName(TEXT("Open Inventory"));
}

FText USettings_Widget::GetSprintActionKeyName()
{
	return GetActionKeyName(TEXT("Sprint"));
}

FText USettings_Widget::GetOpenPauseActionKeyName()
{
	return GetActionKeyName(TEXT("Open Pause Menu"));
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

	return FText::FromString("Unassigned");
}

FText USettings_Widget::GetAxisKeyName(FName const & AxisName)
{
	if (UInputSettings* InputSettings = const_cast<UInputSettings*>(GetDefault<UInputSettings>()))
	{
		TArray<FInputAxisKeyMapping>& AxisKeys = InputSettings->AxisMappings;

		for (auto& Axis : AxisKeys)
		{
			if (Axis.AxisName == AxisName)
			{
				return Axis.Key.GetDisplayName();
			}
		}
	}

	return FText::FromString("Unassigned");
}