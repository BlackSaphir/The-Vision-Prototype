// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Enemy_Character.h"
#include "AI_IdleSubState_HighHP.h"


void UAI_IdleSubState_HighHP::Do(AEnemy_Character* Char)
{
	if (Char->Life < 50)
	{
		Char->CurrentState = (UAI_BaseState*)Char->IdleState;
	}

	if (Char->Distance < 1000)
	{
		Char->CurrentState = (UAI_BaseState*)Char->MoveState;
	}
}



