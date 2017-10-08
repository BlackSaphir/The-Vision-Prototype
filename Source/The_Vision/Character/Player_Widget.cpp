// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Vision.h"
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
	GetReserveAmmo();
}

int UPlayer_Widget::GetAmmo()
{
	if (!character)
	{
		return 0.0f;
	}
	Widget_AmmoRifle = character->Rifle_Ammo;
	return Widget_AmmoRifle;
}

int UPlayer_Widget::GetReserveAmmo()
{
	if (!character)
	{
		return 0.0f;
	}
	Widget_ReserveAmmo = character->Reserve_Ammo;
	return Widget_ReserveAmmo;
}


float UPlayer_Widget::GetHealth()
{
	if (!character)
	{
		return 0.0f;
	}
	Widget_CharacterHealth = character->Character_Health;
	return Widget_CharacterHealth;
}

int UPlayer_Widget::GetGefaehrlichkeitsstufe()
{
	if (!character)
	{
		return 0.0f;
	}
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


