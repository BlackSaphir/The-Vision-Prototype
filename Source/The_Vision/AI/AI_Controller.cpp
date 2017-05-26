// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_Character.h"
#include "AI_Controller.h"

AAI_Controller::AAI_Controller()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard_Component"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree_Component"));
}

void AAI_Controller::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemy_Character* Char = Cast<AEnemy_Character>(InPawn);
	if (Char && Char->BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*Char->BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*Char->BehaviorTree);
	}
}

void AAI_Controller::SetSensedTarget(APawn* NewTarget)
{
	/*if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetKey, NewTarget);
	}*/

	APawn* Pawn = GetPawn();
	AEnemy_Character* Char = Cast<AEnemy_Character>(Pawn);
	Char->BeginMove(NewTarget);
}
