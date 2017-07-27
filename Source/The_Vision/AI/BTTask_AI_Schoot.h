// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <AI/AI_Controller.h>
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy_Character.h"
#include "BTTask_AI_Schoot.generated.h"

/**
 *
 */
UCLASS()
class THE_VISION_API UBTTask_AI_Schoot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:

	void DoDamage(FHitResult const&);

	UPROPERTY(EditAnyWhere)
		class AAI_Controller* AIController;

	UPROPERTY(EditAnyWhere)
		AEnemy_Character* AI_Pawn;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float Normal_Force = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* Monitor_BreakGlass_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float Fire_Delay = 0.465f;

	float delayTimer = 0;

	UFUNCTION()
		void Fire(float LineTraceLenght = 3000, ECollisionChannel CollisionChannel = ECC_Vehicle);
};
