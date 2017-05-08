// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "The_VisionHUD.generated.h"

UCLASS()
class AThe_VisionHUD : public AHUD
{
	GENERATED_BODY()

public:
	AThe_VisionHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

