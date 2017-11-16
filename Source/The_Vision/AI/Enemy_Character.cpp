// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "AI_Controller.h"
#include "The_Vision/Character/The_VisionCharacter.h"

#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DrawDebugHelpers.h"

#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Kismet/KismetMathLibrary.h"
#include "Static_Libary.h"
#include "Enemy_Character.h"
#include <string>


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
	//Last_Player_Position = CreateDefaultSubobject<AActor>(TEXT("Last_Player_Position"));


}

// Called when the game starts or when spawned
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();
	Con = Cast<AAI_Controller>(GetController());
	Con->GetAllWaypoints();
	Char = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());

	Con->BlackboardComp->SetValueAsBool(Con->ArrivedToLastSeenPlayerPosition, false);
	Con->BlackboardComp->SetValueAsFloat(Con->DistanceToLastSeenPlayerPosition, 99999999999999999.9f);

	//spawning actor for tracing purposes of player
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	UWorld* TempWorld = GetWorld();
	Last_Player_Position = TempWorld->SpawnActor<AActor>(last_position_actor, Location, Rotation, SpawnInfo);
}

// Called every frame
void AEnemy_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//setting a few blackboard keys for the ai
	if (Con && Con->BlackboardComp->GetValueAsObject(Con->WaypointKey) == nullptr)
	{
		Con->SetWaypoint();
	}

	if (Con && Con->BlackboardComp->GetValueAsObject(Con->WaypointKey) != nullptr)
	{
		Con->GetDistanceToWaypoint();
	}

	if (Con->BlackboardComp->GetValueAsFloat(Con->DistanceToWaypointKey) < 150.0f)
	{
		Con->SetNextWaypoint();
	}

	if (Con && Con->BlackboardComp->GetValueAsObject(Con->TargetKey) != nullptr)
	{
		const FVector Player_Vector = Char->FirstPersonCamera->GetComponentLocation();
		const FVector Enemy_Camera_Vector = EnemyCamera->GetComponentLocation();
		const FVector Enemy_Camera_ForwardVector = Enemy_Camera_Vector + (EnemyCamera->GetForwardVector() * LineTraceLenght);
		FHitResult hitout2;
		ECollisionChannel collision_channel = ECC_Vehicle;

		UStatic_Libary::LineTrace(GetWorld(), Enemy_Camera_Vector, Enemy_Camera_ForwardVector, hitout2, collision_channel, false);

		///left for debugging purposes
		//DrawDebugLine(GetWorld(), Enemy_Camera_Vector, Enemy_Camera_ForwardVector, FColor::Green, true, 10, 0, 2.f);
		//FString name = hitout2.Actor->GetDebugName(hitout2.GetActor());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s" + name));
	}

	if (Con && Con->BlackboardComp->GetValueAsBool(Con->PawnInSight) == false)
	{
		if (Con && Con->BlackboardComp->GetValueAsObject(Con->SensedPawn_Last_Location) != nullptr)
		{
			Con->BlackboardComp->SetValueAsFloat(Con->DistanceToLastSeenPlayerPosition, GetDistanceTo(dynamic_cast<AActor*>(Con->BlackboardComp->GetValueAsObject(Con->SensedPawn_Last_Location))));
		}
	}

	if (Con && Con->BlackboardComp->GetValueAsFloat(Con->DistanceToLastSeenPlayerPosition) < 50)
	{
		Con->BlackboardComp->SetValueAsBool(Con->ArrivedToLastSeenPlayerPosition, true);
	}

	if (Con && Con->BlackboardComp->GetValueAsBool(Con->PawnInSight) == false && Con->BlackboardComp->GetValueAsBool(Con->ArrivedToLastSeenPlayerPosition) == true)
	{
		Con->SetSensedTarget(NULL);
	}
}

// Called to bind functionality to input
void AEnemy_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy_Character::OnHearNoise(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	if (InVision != true)
	{
		character = PawnInstigator;
		Last_Player_Position->SetActorLocation(PawnInstigator->GetActorLocation());
		if (Con && PawnInstigator != this)
		{
			Con->SetSensedTarget(PawnInstigator);
		}
		if (GetDistanceTo(PawnInstigator) > 1100)
		{
			Con->SetSensedTarget(NULL);
		}
		if (PawnInstigator)
		{
			Con->BlackboardComp->SetValueAsObject(Con->SensedPawn_Last_Location, Last_Player_Position);
		}
	}
}

void AEnemy_Character::OnSeePawn(APawn * PawnInstigator)
{
	if (InVision != true)
	{

		character = PawnInstigator;

		if (PawnInstigator)
		{
			Last_Player_Position->SetActorLocation(PawnInstigator->GetActorLocation());
		}

		if (Con && PawnInstigator != this)
		{
			Con->SetSensedTarget(PawnInstigator);
		}
		if (GetDistanceTo(PawnInstigator) > 1500)
		{
			Con->SetSensedTarget(NULL);
		}
		if (PawnInstigator)
		{

			Con->BlackboardComp->SetValueAsObject(Con->SensedPawn_Last_Location, Last_Player_Position);
			//Foward RayCast
			const FVector Player_Vector = Char->FirstPersonCamera->GetComponentLocation();
			const FVector Enemy_Camera_Vector = EnemyCamera->GetComponentLocation();
			const FVector Enemy_Camera_ForwardVector = Enemy_Camera_Vector + (EnemyCamera->GetForwardVector() * LineTraceLenght);
			FHitResult hitout;
			ECollisionChannel collision_channel = ECC_Vehicle;

			///not relevant now but in later construction of AI
			UStatic_Libary::LineTrace(GetWorld(), Enemy_Camera_Vector, Enemy_Camera_ForwardVector, hitout, collision_channel, false);
			//DrawDebugLine(GetWorld(), Enemy_Camera_Vector, Enemy_Camera_ForwardVector, FColor::Green, true, 10, 0, 2.f);
			if (hitout.Actor != Char)
			{
				Con->SetDistanceToPlayer(PawnInstigator);
			}
			if (hitout.Actor == Char)
			{
				Con->SetDistanceToPlayer(PawnInstigator);
			}
		}
	}
}

void AEnemy_Character::SetLife(int CharDmg)
{
	Health -= CharDmg;
	if (Health <= 0)
	{
		Char->Kills++;
		Char->SetGefaehrlichkeitsstufe();
		Destroy(true);
		Last_Player_Position->Destroy(true);
	}
}

