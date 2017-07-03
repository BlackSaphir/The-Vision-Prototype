// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_Character.h"
#include "EngineUtils.h"
#include "AI_Controller.h"
#include "Engine/Engine.h"

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
		BlackboardComp->SetValueAsFloat(DistanceKey, distance);
		FString name = FString::FromInt((int)distance);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s" + name));
	}
}

void AAI_Controller::GetAllWaypoints()
{
	for (TActorIterator<AWaypoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AWaypoint* Waypoint = *ActorItr;
		Waypoints.Add(Waypoint);
	}
}

void AAI_Controller::SetPatrol()
{
	TArray<float> Waypiontdistance;
	//get all Waypoints
	if (BlackboardComp)
	{
		if (BlackboardComp->GetKeyRawData(TargetKey) == nullptr)
		{
			for (size_t i = 0; i < sizeof(Waypoints); i++)
			{
				Waypiontdistance.Add(GetPawn()->GetDistanceTo(Waypoints[i]));
			}
		}
	}

	//get closest Waypoint through index
	for (size_t i = 0; i < sizeof(Waypiontdistance); i++)
	{
		if (IteratorSaver>Waypiontdistance[i])
		{
			IteratorSaver = Waypiontdistance[i];
			WaypointIndex = i;
		}
	}
	//set closest Waypoint in Blackboard
	BlackboardComp->SetValueAsObject(WaypointKey,Waypoints[WaypointIndex]);
}

