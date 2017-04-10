// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Static_Libary.generated.h"


UCLASS()
class THE_VISION_API UStatic_Libary : public UObject
{

	GENERATED_BODY()


public : 
	
	static bool LineTrace(UWorld* ,  const FVector& , const FVector& , FHitResult& , ECollisionChannel , bool);

	//static bool DanielLineTrace(UObject* WorldContextObject, FVector Start, FVector End, ETraceTypeQuery TraceChannel, FHitResult& Hit);


};	
