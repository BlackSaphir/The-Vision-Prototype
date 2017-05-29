// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "AI_Controller.h"

#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "AI_AttackState.h"
#include "AI_BaseState.h"
#include "AI_IdleState.h"
#include "AI_IdleSubState_HighHP.h"
#include "AI_IdleSubState_LowHP.h"
#include "AI_MoveToState.h"

#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Kismet/KismetMathLibrary.h"
#include "Enemy_Character.h"


// Sets default values
AEnemy_Character::AEnemy_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy_Character::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemy_Character::OnHearNoise);
}

// Called when the game starts or when spawned
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();
	MoveState = NewObject<UAI_MoveToState>(this, UAI_MoveToState::StaticClass(), TEXT("MoveToState_Component"));
	IdleState = NewObject<UAI_IdleState>(this, UAI_IdleState::StaticClass(), TEXT("IdleState_Component"));
	IdleSubState_HighHP = NewObject<UAI_IdleSubState_HighHP>(this, UAI_IdleSubState_HighHP::StaticClass(), TEXT("IdleSubState_HighHP_Component"));
	IdleSubState_LowHP = NewObject<UAI_IdleSubState_LowHP>(this, UAI_IdleSubState_LowHP::StaticClass(), TEXT("IdleSubState_LowHP_Component"));
	AttackState = NewObject<UAI_AttackState>(this, UAI_AttackState::StaticClass(), TEXT("AttackState_Component"));
	CurrentState = IdleState;
}

// Called every frame
void AEnemy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTarget)
	{
		Distance = GetDistanceTo(CurrentTarget);
	}
	if (CurrentState)
	{
		CurrentState->Do(this);
	}
}

// Called to bind functionality to input
void AEnemy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy_Character::OnHearNoise(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	AAI_Controller* Con = Cast<AAI_Controller>(GetController());

	if (Con && PawnInstigator != this)
	{
		Con->SetSensedTarget(PawnInstigator);
	}
}

void AEnemy_Character::OnSeePawn(APawn * PawnInstigator)
{
	CurrentTarget = PawnInstigator;
}

void AEnemy_Character::MoveTo()
{
	/*FVector CurrentTargetLocation = CurrentTarget->GetActorLocation();
	FVector MoveDirection = CurrentTargetLocation - this->GetActorLocation();
	MoveDirection.Normalize();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), CurrentTargetLocation);
	FRotator SelfRotation = this->GetActorRotation();

	float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(this->GetActorForwardVector(), LookAtRotation.Vector())));

	this->AddActorWorldOffset(MoveDirection * Speed * GetWorld()->DeltaTimeSeconds);
	if (AimAtAngle > 1)
	{
		if (SelfRotation.Yaw - LookAtRotation.Yaw <=0)
		{
			this->AddActorWorldRotation(FRotator(0, RoatationSpeed * GetWorld()->DeltaTimeSeconds, 0));
		}
		else if (SelfRotation.Yaw - LookAtRotation.Yaw > 0)
		{
			this->AddActorWorldRotation(FRotator(0, -(RoatationSpeed * GetWorld()->DeltaTimeSeconds), 0));
		}
	}*/
}

void AEnemy_Character::BeginMove(APawn * NewTarget)
{
	CurrentTarget = NewTarget;
}

void AEnemy_Character::SetLife()
{
	if (Life < 50)
	{
		Life = 100;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Life set to 100"));
	}
	else
	{
		Life = 49;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Life set to 49"));


	}
}

