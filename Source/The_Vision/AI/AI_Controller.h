// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
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

protected:

	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly)
		FName TargetKey = "SensedPawn";
};
