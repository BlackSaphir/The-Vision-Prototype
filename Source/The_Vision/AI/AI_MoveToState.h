// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/AI_BaseState.h"
#include "AI_MoveToState.generated.h"

/**
 * 
 */
UCLASS()
class THE_VISION_API UAI_MoveToState : public UAI_BaseState
{
	GENERATED_BODY()
	
public:
	virtual void Do(AEnemy_Character* Char) override;
	
	
	
};
