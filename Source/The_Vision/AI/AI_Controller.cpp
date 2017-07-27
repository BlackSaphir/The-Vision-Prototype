// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_Character.h"
#include "EngineUtils.h"
#include "AI_Controller.h"
#include "Engine/Engine.h"
#include "Static_Libary.h"
#include "DrawDebugHelpers.h"
#include "Character/The_VisionCharacter.h"

AAI_Controller::AAI_Controller()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard_Component"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree_Component"));
}

void AAI_Controller::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemy_Character* PossesedPawn = Cast<AEnemy_Character>(InPawn);
	if (PossesedPawn && PossesedPawn->BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*PossesedPawn->BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*PossesedPawn->BehaviorTree);
	}

	SpawnPointIndex = GetSpawnPointIndex();
}

void AAI_Controller::SetSensedTarget(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetKey, NewTarget);
	}
}

void AAI_Controller::SetDistanceToPlayer(APawn *Player)
{
	if (BlackboardComp)
	{
		float distance = GetPawn()->GetDistanceTo(Player);
		BlackboardComp->SetValueAsFloat(DistanceToPlayerKey, distance);
		//FString name = FString::FromInt((int)distance);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s" + name));
	}
}

void AAI_Controller::GetDistanceToWaypoint()
{
	if (BlackboardComp)
	{
		AActor* Waypoint = Cast<AActor>(BlackboardComp->GetValueAsObject(WaypointKey));
		float distance = GetPawn()->GetDistanceTo(Waypoint);
		BlackboardComp->SetValueAsFloat(DistanceToWaypointKey, distance);
		FString name = FString::FromInt((int)distance);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s" + name));
	}
}

void AAI_Controller::GetAllWaypoints()
{
	//get all Waypoints
	for (TActorIterator<AWaypoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AWaypoint* Waypoint = *ActorItr;
		if (Waypoint->WaypointIndex == SpawnPointIndex)
		{
			Waypoints.Add(Waypoint);
		}
	}
}

void AAI_Controller::SetWaypoint()
{

	//get all Waypointsdistances
	if (BlackboardComp)
	{
		if (BlackboardComp->GetValueAsObject(TargetKey) == nullptr)
		{
			for (size_t i = 0; i < Waypoints.Num(); i++)
			{
				Waypointdistance.Add(GetPawn()->GetDistanceTo(Waypoints[i]));
			}
		}
	}

	//get closest Waypoint through index
	for (size_t i = 0; i < Waypointdistance.Num(); i++)
	{
		if (IteratorSaver > Waypointdistance[i])
		{
			IteratorSaver = Waypointdistance[i];
			WaypointArrayIndex = i;
		}
	}
	//set closest Waypoint in Blackboard
	BlackboardComp->SetValueAsObject(WaypointKey, Waypoints[WaypointArrayIndex]);
}

void AAI_Controller::SetNextWaypoint()
{
	if (WaypointArrayIndex < Waypoints.Num() - 1)
	{
		WaypointArrayIndex++;
	}
	else
	{
		WaypointArrayIndex = 0;
	}
	BlackboardComp->SetValueAsObject(WaypointKey, Waypoints[WaypointArrayIndex]);
}

int32 AAI_Controller::GetSpawnPointIndex()
{
	for (TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASpawnPoint* SpawnPoint = *ActorItr;
		SpawnPoints_Array.Add(SpawnPoint);
	}


	for (size_t i = 0; i < SpawnPoints_Array.Num(); i++)
	{
		SpawnPointdistance.Add(GetPawn()->GetDistanceTo(SpawnPoints_Array[i]));
	}


	for (size_t i = 0; i < SpawnPointdistance.Num(); i++)
	{
		if (SpawnIteratorSaver > SpawnPointdistance[i])
		{
			SpawnIteratorSaver = SpawnPointdistance[i];
			SpawnPointArrayIndex = i;
		}
	}

	return SpawnPoints_Array.Num() > 0 ? SpawnPoints_Array[SpawnPointArrayIndex]->SpawnpointIndex : 0;
}


