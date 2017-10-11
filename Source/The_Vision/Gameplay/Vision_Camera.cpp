// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "Vision_Camera.h"

AVision_Camera::AVision_Camera()
{
}

void AVision_Camera::BeginPlay()
{
	Super::BeginPlay();

	this->Tags.Add(CameraTag);

}
