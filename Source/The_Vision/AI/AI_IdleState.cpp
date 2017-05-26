// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Enemy_Character.h"
#include "EngineGlobals.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "AI_IdleState.h"

void UAI_IdleState::Do(AEnemy_Character* Char)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("IdleState"));
	if (Char->Life < 50)
	{
		Char->CurrentState = (UAI_BaseState*)Char->IdleSubState_LowHP;
	}
	else
	{
		Char->CurrentState = (UAI_BaseState*)Char->IdleSubState_HighHP;
	}
}


