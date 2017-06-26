// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy_Character.generated.h"

class UAI_AttackState;
class UAI_BaseState;
class UAI_IdleState;
class UAI_IdleSubState_HighHP;
class UAI_IdleSubState_LowHP;
class UAI_MoveToState;
class AThe_VisionCharacter;


UCLASS()
class THE_VISION_API AEnemy_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Functions

public:

	

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
		void OnSeePawn(APawn *PawnInstigator);

	UFUNCTION()
		void SetLife();

	

	//Variable

public:

	UPROPERTY(VisibleAnyWhere)
 		UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere)
		AActor* CurrentTarget;

	UPROPERTY(EditAnyWhere)
		int Life = 100;

	UPROPERTY(EditAnyWhere)
		class UCameraComponent* EnemyCamera;

	UPROPERTY(EditAnyWhere)
		class AThe_VisionCharacter* Char;
};
