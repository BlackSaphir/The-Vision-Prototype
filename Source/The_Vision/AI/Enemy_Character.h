// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI_Controller.h"
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

	// Functions
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
		void OnSeePawn(APawn *PawnInstigator);

	UFUNCTION()
		void SetLife();

	//Variable

public:
	UPROPERTY(EditAnyWhere)
		class UCameraComponent* EnemyCamera;

	UPROPERTY(VisibleAnyWhere)
 		UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere)
		AActor* CurrentTarget;

	UPROPERTY(EditAnyWhere)
		int Life = 100;

	UPROPERTY(EditAnyWhere)
		float LineTraceLenght = 1500.0f;

	UPROPERTY(EditAnyWhere)
		class AThe_VisionCharacter* Char;

	UPROPERTY(EditAnyWhere)
		class AAI_Controller* Con;

	UPROPERTY(EditAnyWhere)
		FVector Player_Vector;

	UPROPERTY(EditAnyWhere)
		FVector Enemy_Camera_Vector;

	UPROPERTY(EditAnyWhere)
		FVector Enemy_Camera_ForwardVector;

	FHitResult hitout;
	FHitResult hitout2;
	ECollisionChannel collision_channel = ECollisionChannel::ECC_Vehicle;
};
