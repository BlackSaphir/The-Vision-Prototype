// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Destructible_DamageType.h"

UDestructible_DamageType::UDestructible_DamageType(const FObjectInitializer& ObjectInitializer)	: Super(ObjectInitializer)
{
	bCausedByWorld = false;
	bScaleMomentumByMass = true;
	DamageFalloff = 1.0f;

	bRadialDamageVelChange = false;
	DamageImpulse = 200000.0f;

	DestructibleImpulse = 200000.0f;
	DestructibleDamageSpreadScale = 1.0f;
}


