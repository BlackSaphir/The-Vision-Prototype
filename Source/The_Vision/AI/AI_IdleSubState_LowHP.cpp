// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "EngineUtils.h"
//#include "Point.h"
#include "Enemy_Character.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "AI_IdleSubState_LowHP.h"


void UAI_IdleSubState_LowHP::Do(AEnemy_Character* Char)
{
	//if (Char->life>50)
	//{
	//	Char->currentState = (UBaseState*)Char->idleState;
	//}

	//if (UWorld*World = Char->GetWorld())
	//{
	//	for (TActorIterator<APoint> ActorItr(World); ActorItr; ++ActorItr)
	//	{
	//		APoint *Point = *ActorItr;
	//		Points.Add(Point);
	//	}
	//	int RandIndex = rand() % 4;
	//	//Pawn= NewObject<APawn>(this, APawn::StaticClass(), TEXT("Pawn"));
	//	//Pawn->SetActorLocation(Points[RandIndex]->GetActorLocation());
	//	Char->CurrentTarget = Points[RandIndex];
	//	Char->currentState = (UBaseState*)Char->moveState;
	//}
}

