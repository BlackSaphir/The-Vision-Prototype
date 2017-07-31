// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
#include "The_VisionCharacter.h"
#include "EngineUtils.h"
#include "Player_Widget.h"

void UPlayer_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	//FindPlayer();
	
	character = Cast<AThe_VisionCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}

void UPlayer_Widget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	GetAmmo();
}

float UPlayer_Widget::GetAmmo()
{
	Widget_AmmoRifle = character->Rifle_Ammo;
	return Widget_AmmoRifle;
}

float UPlayer_Widget::GetHealth()
{
	Widget_CharacterHealth = character->Character_Health;
	return Widget_CharacterHealth;
}

int UPlayer_Widget::GetGefaehrlichkeitsstufe()
{
	return character->Gefaehrlichkeitsstufe;
		

}

//void UPlayer_Widget::FindPlayer()
//{
//	if (UWorld* world = GetWorld())
//	{
//		for (TActorIterator<AThe_VisionCharacter> ActorIter(world);ActorIter;++ActorIter)
//		{
//			if (AThe_VisionCharacter* visioncharacter = *ActorIter)
//			{
//				character = visioncharacter;
//				Widget_AmmoRifle = visioncharacter->Rifle_Ammo;
//				Widget_CharacterHealth = visioncharacter->Character_Health;
//			}
//		}
//	}
//}


