// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AI/Waypoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class THE_VISION_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	AAI_Controller();
	
	virtual void Possess(APawn* InPawn) override;
	void SetSensedTarget(APawn* NewTarget);
	void SetDistanceToPlayer(APawn *Player);
	void GetAllWaypoints();
	void SetPatrol();

protected:

	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly)
		FName TargetKey = "SensedPawn";

	UPROPERTY(EditDefaultsOnly)
		FName DistanceKey = "DistanceKey";

	UPROPERTY(EditDefaultsOnly)
		FName WaypointKey = "WaypointKey";

	UPROPERTY(EditDefaultsOnly)
		TArray<AWaypoint*> Waypoints;

	UPROPERTY(EditDefaultsOnly)
		int WaypointIndex=0;

	UPROPERTY(EditDefaultsOnly)
		float IteratorSaver = 99999999999999999.9f;
};
