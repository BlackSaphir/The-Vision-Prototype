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

USTRUCT(BlueprintType)
struct FVisionInputActionKeyMapping
{
	GENERATED_BODY()

public:

	/** Friendly name of action, e.g "jump" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FName ActionName;

	/** Key to bind it to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FKey Key;

	/** true if one of the Shift keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint8 bShift : 1;

	/** true if one of the Ctrl keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint8 bCtrl : 1;

	/** true if one of the Alt keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint8 bAlt : 1;

	/** true if one of the Cmd keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		uint8 bCmd : 1;

public:

	FVisionInputActionKeyMapping()
	{
	}

	FVisionInputActionKeyMapping(FInputActionKeyMapping const& InputActionKeyMapping)
	{
		ActionName = InputActionKeyMapping.ActionName;
		Key = InputActionKeyMapping.Key;
		bShift = InputActionKeyMapping.bShift;
		bCtrl = InputActionKeyMapping.bCtrl;
		bAlt = InputActionKeyMapping.bAlt;
		bCmd = InputActionKeyMapping.bCmd;
	}

	static FInputActionKeyMapping ConvertActionMapping(FVisionInputActionKeyMapping const& VisionInputActionKeyMapping);
};

USTRUCT(BlueprintType)
struct FVisionInputAxisKeyMapping
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FName AxisName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float Scale = 1;

public:

	FVisionInputAxisKeyMapping()
	{
	}

	FVisionInputAxisKeyMapping(FInputAxisKeyMapping const& InputAxisKeyMapping)
	{
		AxisName = InputAxisKeyMapping.AxisName;
		Key = InputAxisKeyMapping.Key;
		Scale = InputAxisKeyMapping.Scale;
	}


	static FInputAxisKeyMapping ConvertAxisMapping(FVisionInputAxisKeyMapping const& VisionInputAxisKeyMapping);

};

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

	UFUNCTION(BlueprintCallable, Category = Key)
		bool RemapActionKey(const FVisionInputActionKeyMapping& newActionMapping);

	UFUNCTION(BlueprintCallable, Category = Key)
		bool RemapAxisKey(const FVisionInputAxisKeyMapping & newAxisMapping);


	UFUNCTION(BlueprintPure, Category = Key)
		FText GetFireActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetZoomActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetReloadActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetInteractActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetOpenInventoryActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetSprintActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText GetOpenPauseActionKeyName();

	UFUNCTION(BlueprintPure, Category = Key)
		FText MoveForwardKeyName();



private:

	FText GetActionKeyName(FName const& ActionName);

	FText GetAxisKeyName(FName const& AxisName);
};
