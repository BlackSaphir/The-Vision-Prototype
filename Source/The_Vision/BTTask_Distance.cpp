// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "AI/AI_Controller.h"
#include "Character/The_VisionCharacter.h"
#include "BTTask_Distance.h"


EBTNodeResult::Type UBTTask_Distance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AThe_VisionCharacter* character = dynamic_cast<AThe_VisionCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto MyController = Cast<AAIController>(OwnerComp.GetAIOwner());
	float distance = MyController->GetPawn()->GetDistanceTo(character);
	if (distance<10000000)
	{
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
