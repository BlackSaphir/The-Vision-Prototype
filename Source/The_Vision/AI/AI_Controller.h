// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AI/Waypoint.h"
#include "AI/SpawnPoint.h"
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
	void GetDistanceToWaypoint();
	void GetAllWaypoints();
	void SetWaypoint();
	void SetNextWaypoint();
	int32 GetSpawnPointIndex();

	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly)
		FName WaypointKey = "WaypointKey";

	UPROPERTY(EditDefaultsOnly)
		FName DistanceToWaypointKey = "DistanceToWaypointKey";

protected:


	UPROPERTY(EditDefaultsOnly)
		FName TargetKey = "SensedPawn";

	UPROPERTY(EditDefaultsOnly)
		FName DistanceToPlayerKey = "DistanceToPlayerKey";

	UPROPERTY(EditDefaultsOnly)
		TArray<AActor*> Waypoints;

	UPROPERTY(EditDefaultsOnly)
		TArray<ASpawnPoint*> SpawnPoints_Array;

	UPROPERTY(EditDefaultsOnly)
	TArray<float> Waypointdistance;

	UPROPERTY(EditDefaultsOnly)
		TArray<float> SpawnPointdistance;

	UPROPERTY(EditDefaultsOnly)
		int WaypointArrayIndex=0;

	UPROPERTY(EditDefaultsOnly)
		int SpawnPointArrayIndex = 0;

	UPROPERTY(EditDefaultsOnly)
		int SpawnPointIndex;

	UPROPERTY(EditDefaultsOnly)
		float IteratorSaver = 99999999999999999.9f;

	UPROPERTY(EditDefaultsOnly)
		float SpawnIteratorSaver = 99999999999999999.9f;
};