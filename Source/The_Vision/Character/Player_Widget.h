// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "The_VisionCharacter.h"
#include "Player_Widget.generated.h"

/**
 * 
 */
UCLASS()
class THE_VISION_API UPlayer_Widget : public UUserWidget
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere,Category = Bullet)
	float Widget_AmmoRifle;
	
	UPROPERTY(EditAnywhere, Category = Character)
	float Widget_CharacterHealth;

	UFUNCTION(BlueprintCallable, Category = Bullet)
		float GetAmmo();

	UFUNCTION(BlueprintCallable, Category = Character)
		float GetHealth();

	UFUNCTION(BlueprintCallable, Category = Character)
		int GetGefaehrlichkeitsstufe();
	
private:
	void FindPlayer();
	AThe_VisionCharacter* character;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
	
};
