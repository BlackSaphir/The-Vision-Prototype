// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "BeginLevel_Interface.h"

// This function does not need to be modified.
UBeginLevel_Interface::UBeginLevel_Interface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Add default functionality here for any IBeginLevel_Interface functions that are not pure virtual.


void IBeginLevel_Interface::BeginLevel()
{
	BPEvent_BeginLevel();
}
