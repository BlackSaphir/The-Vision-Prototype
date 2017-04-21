// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "The_Vision.h"
#include "Game/The_VisionGameMode.h"
#include "Game/The_VisionHUD.h"
#include "Character/The_VisionCharacter.h"

AThe_VisionGameMode::AThe_VisionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	//HUDClass = AThe_VisionHUD::StaticClass();
}
