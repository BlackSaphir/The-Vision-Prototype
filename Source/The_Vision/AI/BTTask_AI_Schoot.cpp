// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Character/The_VisionCharacter.h"
#include "BTTask_AI_Schoot.h"
#include "Animation/AnimInstance.h"
#include "Static_Libary.h"
#include "Enemy_Character.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "DamageTypes/Destructible_DamageType.h"
#include "Kismet/KismetMathLibrary.h"


EBTNodeResult::Type UBTTask_AI_Schoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AThe_VisionCharacter* character = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AIController = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	AI_Pawn = Cast<AEnemy_Character>(AIController->GetPawn());
	delayTimer += GetWorld()->DeltaTimeSeconds;

	//Rotation to player 
	FVector instigatorlocation =character->GetActorLocation();
	FRotator selfRotation = AI_Pawn->GetActorRotation();
	FVector pawnlocation = AI_Pawn->GetActorLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(pawnlocation, instigatorlocation);

	float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(AI_Pawn->GetActorForwardVector(), lookAtRotation.Vector())));
	float RoatationSpeed = 300;

	if (AimAtAngle > 10)
	{
		if (selfRotation.Yaw - lookAtRotation.Yaw <= 0)
		{
			AI_Pawn->AddActorWorldRotation(FRotator(0, RoatationSpeed*GetWorld()->DeltaTimeSeconds, 0));
		}
		else if (selfRotation.Yaw - lookAtRotation.Yaw > 0)
		{
			AI_Pawn->AddActorWorldRotation(FRotator(0, -(RoatationSpeed*GetWorld()->DeltaTimeSeconds), 0));
		}
	}

	if (delayTimer > Fire_Delay)
	{
		Fire();
		delayTimer = 0;
	}
	return EBTNodeResult::Succeeded;
}

void UBTTask_AI_Schoot::DoDamage(FHitResult const& HitOut)
{
	AThe_VisionCharacter* character = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (HitOut.GetActor() == character)
	{
		if (character->Character_Health <= Damage)
		{
			character->Character_Health = 0;
			character->SetLife(0);
		}
		else
		{
			character->SetLife(Damage);
		}
	}

	FVector Force_Vector = HitOut.TraceEnd - HitOut.TraceStart;
	Force_Vector.Normalize();

	if (HitOut.GetActor()->ActorHasTag("Monitor"))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Monitor_BreakGlass_Sound, HitOut.Location);
	}

	UPrimitiveComponent* Hit_Component = HitOut.GetComponent();
	/*Hit_Component->AddImpulse(Force_Vector * Normal_Force, NAME_None, true);*/

	if (ADestructibleActor* HitActor = Cast<ADestructibleActor>(HitOut.GetActor()))
	{
		if (HitActor->ActorHasTag("Cube"))
		{
			UGameplayStatics::ApplyRadialDamage(GetWorld(), 30.0f, HitOut.Location, 15.0f, UDestructible_DamageType::StaticClass(), TArray<AActor*>(), AIController->GetPawn());
		}
	}
	//AThe_VisionCharacter* character = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//if (HitOut.GetActor()==character)
	//{
	//	Hit_Component->AddImpulse(Force_Vector * Normal_Force);
	//}
}
//
void UBTTask_AI_Schoot::Fire(float LineTraceLenght, ECollisionChannel CollisionChannel)
{
	AThe_VisionCharacter* character = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//		//location the PC is focused on
	const FVector Start = AI_Pawn->EnemyCamera->GetComponentLocation();

	//LineTraceLenght in facing direction of PC 
	const FVector End = Start + (AI_Pawn->EnemyCamera->GetForwardVector() * LineTraceLenght);

	//		//The trace data is stored here
	FHitResult HitOut;

	bool ReturnPhysMat = false;
	if (character->Character_Health > 0)
	{
		if (UWorld* World = GetWorld())
		{
			if (UStatic_Libary::LineTrace(World, Start, End, HitOut, CollisionChannel, ReturnPhysMat))
			{
				DoDamage(HitOut);
			}
			UGameplayStatics::PlaySoundAtLocation(World, FireSound, HitOut.TraceStart);
		}
	}
}

