// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "The_VisionCharacter.generated.h"


class UInputComponent;

UCLASS(config = Game)
class AThe_VisionCharacter : public ACharacter
{
	GENERATED_BODY()

		// Component

public:

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCamera;

	

	// Variable

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AThe_VisionProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* Monitor_BreakGlass_Sound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnyWhere)
		UDecalComponent* Fade;

	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AActor> Bullet_Hole_Decal;

	UPROPERTY(EditAnywhere, Category = Widgets)
		TSubclassOf<class UUserWidget> Lose_Screen_Widget;

	UPROPERTY(EditAnywhere, Category = Widgets)
		TSubclassOf<class UUserWidget> Win_Screen_Widget;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float Destructible_Force = 1000;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float Normal_Force = 1000;

	UPROPERTY(EditAnywhere, Category = Projectile)
		int Rifle_Ammo = 0;

	UPROPERTY(EditAnywhere, Category = Projectile)
		int Reserve_Ammo = 0;

	UPROPERTY(EditAnywhere)
		float Character_Health = 100;

	UPROPERTY(VisibleAnywhere)
		class AInventory_Manager* Inventory_Manager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<class UUserWidget> W_Inventory;


	UPROPERTY(EditAnywhere, Category = Projectile)
		float Fire_Delay = 0.1f;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float Reload_Delay = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

	UPROPERTY(VisibleAnywhere)
		int Kills = 0;

	UPROPERTY(VisibleAnywhere)
		int KillsBefore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gefaehrlichkeitsstufe)
		int Gefaehrlichkeitsstufe = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
		bool InVision;
	
private:

	UUserWidget* inventory_widget;
	float camera_zoom;
	float run_speed = 600;
	float walk_speed = 200;
	float delayTimer = 0;
	bool bMoveForwardPressed;
	bool bMoveBackwardPressed;
	bool bMoveRightPressed;
	bool bMoveLeftPressed;
	bool bLeftMousePressed;

	bool bStartTimer;
	


	// Functions

public:
	AThe_VisionCharacter();

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCamera; }

	UFUNCTION(BlueprintCallable)
		void Fire(float LineTraceLenght = 3000, ECollisionChannel CollisionChannel = ECC_GameTraceChannel2);

	UFUNCTION()
		void SetLife(int AIDmg);	

	UFUNCTION(BlueprintCallable, Category = AI)
		void ReportNoise(USoundBase* SoundToPlay, float Volume);

	UFUNCTION()
		void SetGefaehrlichkeitsstufe();

	UFUNCTION(BlueprintImplementableEvent)
		void Death();

	UFUNCTION(BlueprintCallable, Category = Input)
		void ResetInputs();

		void AddReserveAmmo(int value);

protected:
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);

	/** Fires a projectile. */
	void OnFirePressed();
	void OnFireReleased();

	// Opens bInventory
	void Open_Inventory();
	void Close_Inventory();

	// Zoom
	void Start_Zooming();
	void Stop_Zooming();

	// Sprint
	void Start_Sprint();
	void Stop_Sprint();


	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false; Location = FVector::ZeroVector; }
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);

	void SpawnBulletHole(FHitResult const&);
	void DoDamage(FHitResult const&);

	void FindInventoryManager();

	void Interact();
	TouchData	TouchItem;

	void Reload_Pressed();
	void Reload();

	void Move_Forward();
	void Move_Backward();
	void Move_Left();
	void Move_Right();

	
	void Move_ForwardPressed();
	void Move_ForwardReleased();
	void Move_BackwardPressed();
	void Move_BackwardReleased();
	void Move_LeftPressed();
	void Move_LeftReleased();
	void Move_RightPressed();
	void Move_RightReleased();


	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);


private:
	float TapTimer = 4.97f;
	float Shootingdelay = 0.5f;
	float TapDelay = 0;
	bool StartTimer = false;

};

