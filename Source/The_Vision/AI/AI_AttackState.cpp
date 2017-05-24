// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Enemy_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineGlobals.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "AI_AttackState.h"

void::UAI_AttackState::Do(AEnemy_Character* Char)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("AttackState"));

	FVector currentTargetLocation = Char->CurrentTarget->GetActorLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(Char->GetActorLocation(), currentTargetLocation);
	FRotator selfRotation = Char->GetActorRotation();

	float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(Char->GetActorForwardVector(), lookAtRotation.Vector())));

	if (AimAtAngle > 1)
	{
		if (selfRotation.Yaw - lookAtRotation.Yaw <= 0)
		{
			Char->AddActorWorldRotation(FRotator(0, Char->RoatationSpeed*Char->GetWorld()->DeltaTimeSeconds, 0));
		}
		else if (selfRotation.Yaw - lookAtRotation.Yaw > 0)
		{
			Char->AddActorWorldRotation(FRotator(0, -(Char->RoatationSpeed*Char->GetWorld()->DeltaTimeSeconds), 0));
		}
		if (Char->distance > 100)
		{
			Char->currentState = (U_AI_BaseState*)Char->moveState;
		}
	}*/
}


