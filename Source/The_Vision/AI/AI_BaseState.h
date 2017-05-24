// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AI_BaseState.generated.h"

class AEnemy_Character;

/**
 * 
 */
UCLASS()
class THE_VISION_API UAI_BaseState : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void Do(AEnemy_Character* Char);
	
	
};
