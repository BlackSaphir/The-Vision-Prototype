// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Enemy_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineGlobals.h"
#include "string.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "AI_MoveToState.h"


void UAI_MoveToState::Do(AEnemy_Character* Char)
{
	if (Char->CurrentTarget==nullptr)
	{
		return;
	}

	if (Char->Life < 50)
	{
		Char->Speed = 300;
	}
	else
	{
		Char->Speed = 200;
	}

	FVector CurrentTargetLocation = Char->CurrentTarget->GetActorLocation();
	FVector MoveDirection = CurrentTargetLocation - Char->GetActorLocation();
	MoveDirection.Normalize();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Char->GetActorLocation(), CurrentTargetLocation);
	FRotator SelfRotation = Char->GetActorRotation();

	float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(Char->GetActorForwardVector(), LookAtRotation.Vector())));

	Char->AddActorWorldOffset(MoveDirection *Char->Speed *Char->GetWorld()->DeltaTimeSeconds);

	if (AimAtAngle)
	{
		if (SelfRotation.Yaw - LookAtRotation.Yaw <= 0)
		{
			Char->AddActorWorldRotation(FRotator(0, Char->RoatationSpeed *Char->GetWorld()->DeltaTimeSeconds, 0));
		}
		else if (SelfRotation.Yaw - LookAtRotation.Yaw > 0)
		{
			Char->AddActorWorldRotation(FRotator(0, -(Char->RoatationSpeed *Char->GetWorld()->DeltaTimeSeconds), 0));
		}
	}

	if (Char->Distance > 1000)
	{
		if (Char->CurrentTarget->ActorHasTag("Player"))
		{
			Char->CurrentState = (UAI_BaseState*)Char->IdleState;
		}
	}
	else if (Char->Distance < 100)
	{
		if (Char->CurrentTarget->ActorHasTag("Player"))
		{
			Char->CurrentState = (UAI_BaseState*)Char->AttackState;
		}
		else
		{
			Char->CurrentState = (UAI_BaseState*)Char->IdleState;
		}
	}
}


