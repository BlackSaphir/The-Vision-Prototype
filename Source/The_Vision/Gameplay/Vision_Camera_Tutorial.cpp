// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Vision_Camera_Tutorial.h"

void AVision_Camera_Tutorial::BeginPlay()
{
	Super::BeginPlay();

	this->Tags.Add(CameraTag);
}
