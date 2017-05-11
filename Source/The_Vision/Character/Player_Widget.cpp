// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "The_VisionCharacter.h"
#include "EngineUtils.h"
#include "Player_Widget.h"

void UPlayer_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	FindPlayer();
	//AThe_VisionCharacter* character = FindPlayer();//Cast<AThe_VisionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	/*AmmoRifle = character->Rifle_Ammo;
	CharacterHealth = character->Character_Health;*/
}

void UPlayer_Widget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	GetAmmo();
}

float UPlayer_Widget::GetAmmo()
{
	AmmoRifle = character->Rifle_Ammo;
	return AmmoRifle;
}
void UPlayer_Widget::FindPlayer()
{
	if (UWorld* world = GetWorld())
	{
		for (TActorIterator<AThe_VisionCharacter> ActorIter(world);ActorIter;++ActorIter)
		{
			if (AThe_VisionCharacter* visioncharacter = *ActorIter)
			{
				character = visioncharacter;
				AmmoRifle = visioncharacter->Rifle_Ammo;
				CharacterHealth = visioncharacter->Character_Health;
			}
		}
	}
}


