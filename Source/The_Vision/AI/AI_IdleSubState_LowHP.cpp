// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "EngineUtils.h"
#include "Waypoint.h"
#include "Enemy_Character.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "AI_IdleSubState_LowHP.h"


void UAI_IdleSubState_LowHP::Do(AEnemy_Character* Char)
{
	if (Char->Life > 50)
	{
		Char->CurrentState = (UAI_BaseState*)Char->IdleState;
	}

	if (UWorld*World = Char->GetWorld())
	{
		for (TActorIterator<AWaypoint> ActorItr(World); ActorItr; ++ActorItr)
		{
			AWaypoint *Point = *ActorItr;
			Points.Add(Point);
		}
		int RandIndex = rand() % 4;
		//Pawn= NewObject<APawn>(this, APawn::StaticClass(), TEXT("Pawn"));
		//Pawn->SetActorLocation(Points[RandIndex]->GetActorLocation());
		Char->CurrentTarget = Points[RandIndex];
		Char->CurrentState = (UAI_BaseState*)Char->MoveState;
	}
}

