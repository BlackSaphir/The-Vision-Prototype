// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Static_Libary.h"
#include "Kismet/KismetSystemLibrary.h"





bool UStatic_Libary::LineTrace(UWorld* World,  const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel CollisionChannel = ECC_Pawn, bool ReturnPhysMat = false)
{
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	

	HitOut = FHitResult(ForceInit);

	//Trace
	World->LineTraceSingleByChannel(HitOut, Start, End, CollisionChannel, TraceParams);	


	return (HitOut.GetActor() != NULL);
}

bool UStatic_Libary::SecondLineTrace(UObject* WorldContextObject, FVector Start, FVector End, ETraceTypeQuery TraceChannel,  FHitResult& Hit)
{
	return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, TraceChannel, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, Hit, true);
}
