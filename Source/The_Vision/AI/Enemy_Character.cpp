// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "AI_Controller.h"

#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DrawDebugHelpers.h"

#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "The_Vision/Character/The_VisionCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Static_Libary.h"
#include "Enemy_Character.h"


// Sets default values
AEnemy_Character::AEnemy_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTreeReference"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy_Character::OnSeePawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemy_Character::OnHearNoise);
	EnemyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	EnemyCamera->SetupAttachment(GetCapsuleComponent());
	EnemyCamera->RelativeLocation = FVector(0, 0, 70.0f); // Position the camera
	EnemyCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();
	Con = Cast<AAI_Controller>(GetController());
}

// Called every frame
void AEnemy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Con->GetBlackboardComponent())
	{
		Con->SetPatrol();
	}
}

// Called to bind functionality to input
void AEnemy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy_Character::OnHearNoise(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	if (Con && PawnInstigator != this)
	{
		Con->SetSensedTarget(PawnInstigator);
	}
	if (GetDistanceTo(PawnInstigator)>1100)
	{
		Con->SetSensedTarget(NULL);
	}
}

void AEnemy_Character::OnSeePawn(APawn * PawnInstigator)
{
	FHitResult hitout;
	ECollisionChannel collision_channel = ECollisionChannel::ECC_Vehicle;
	const FVector Start = EnemyCamera->GetComponentLocation();
	Char = dynamic_cast<AThe_VisionCharacter*>(PawnInstigator);
	FVector player = Char->FirstPersonCamera->GetComponentLocation();
	


	if (Con && PawnInstigator != this)
	{
		Con->SetSensedTarget(PawnInstigator);
	}
	if (GetDistanceTo(PawnInstigator)>1500)
	{
		Con->SetSensedTarget(NULL);
	}
	if (PawnInstigator)
	{
		UStatic_Libary::UStatic_Libary::LineTrace(GetWorld(), Start, player, hitout, collision_channel, false);
		DrawDebugLine(GetWorld(), Start,player, FColor::Green, true, 10, 0, 2.f);
		if (hitout.Actor != Char)
		{
			//FString name = hitout.Actor->GetDebugName(hitout.GetActor());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s"+name));
			Con->SetDistanceToPlayer(PawnInstigator);
		}
	}
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

