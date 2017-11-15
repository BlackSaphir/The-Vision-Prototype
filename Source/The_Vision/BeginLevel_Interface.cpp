// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "BeginLevel_Interface.h"


// Add default functionality here for any IBeginLevel_Interface functions that are not pure virtual.

void IBeginLevel_Interface::BeginLevel()
{
	BPEvent_BeginLevel();
}
