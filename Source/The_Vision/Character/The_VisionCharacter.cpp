// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "The_Vision.h"
#include "The_VisionCharacter.h"
//#include "Game/The_VisionProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
#include "MotionControllerComponent.h"
#include "Static_Libary.h"
#include "DrawDebugHelpers.h"
#include "Color.h"

#include "The_Vision/AI/Enemy_Character.h"

//#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
//#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "ActivationInterface.h"
#include "Coreminimal.h"
#include "PhysicsEngine/DestructibleActor.h"
#include "Kismet/KismetMathLibrary.h"
//#include "Components/PrimitiveComponent.h"
#include "Inventory/Inventory_Manager.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "DamageTypes/Destructible_DamageType.h"
#include "Runtime/Engine/Classes/Components/PawnNoiseEmitterComponent.h"
#include "AIBlueprintHelperLibrary.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AThe_VisionCharacter

void AThe_VisionCharacter::SetLife(int AIDmg)
{
	if (Character_Health <= 0)
	{
		Character_Health = 0;
		Death();
	}

	if (Character_Health >= 0)
	{
		Character_Health -= AIDmg;
	}
}

void AThe_VisionCharacter::SetGefaehrlichkeitsstufe()
{
	if (Kills == KillsBefore + 2)
	{
		Gefaehrlichkeitsstufe++;
		KillsBefore = Kills;
	}

}


AThe_VisionCharacter::AThe_VisionCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FName CameraSocket = TEXT("bad_guy_char_Head");
	FirstPersonCamera->SetupAttachment(GetMesh(), CameraSocket);
	FirstPersonCamera->RelativeLocation = FVector(0, 0, 0); // Position the camera
	FQuat Rotation(0, 0, -90, 0);
	FirstPersonCamera->SetRelativeRotation(Rotation);
	FirstPersonCamera->AttachTo(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	//Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	//Mesh1P->SetOnlyOwnerSee(true);
	//Mesh1P->SetupAttachment(FirstPersonCamera);
	//Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	//Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	//Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);


	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.


	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter_Component"));
}

void AThe_VisionCharacter::ResetInputs()
{
	bMoveForwardPressed = false;
	bMoveBackwardPressed = false;
	bMoveRightPressed = false;
	bMoveLeftPressed = false;
	bLeftMousePressed = false;
}

void AThe_VisionCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	FindInventoryManager();

	camera_zoom = FirstPersonCamera->FieldOfView;

	StartTimer = true;
}

void AThe_VisionCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	///*if (bLeftMousePressed)
	//{
	//	GLog->Log(FString(TEXT("Hallo Bool: %s"), bLeftMousePressed ? TEXT("True") : TEXT("False")));
	//	Fire();
	//}*/

	//if (bLeftMousePressed)
	//{
	//	StartTimer = true;
	//	if (StartTimer)
	//	{
	//		Fire();
	//	}

	//	/*if (Tapping(deltaTime))
	//	{
	//		Fire();
	//		GLog->Log(FString(TEXT("Fired by Tapping")));
	//	}*/
	//}

	////rapidfire
	///*if (bLeftMousePressed)
	//{
	//	delayTimer += deltaTime;
	//	if (delayTimer > Shootingdelay)
	//	{
	//		Fire();
	//		delayTimer = 0;
	//	}
	//}*/

	if (bMoveForwardPressed)
	{
		Move_Forward();
	}

	if (bMoveBackwardPressed)
	{
		Move_Backward();
	}

	if (bMoveRightPressed)
	{
		Move_Right();
	}

	if (bMoveLeftPressed)
	{
		Move_Left();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThe_VisionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AThe_VisionCharacter::Interact);

	PlayerInputComponent->BindAction("Open Inventory", IE_Pressed, this, &AThe_VisionCharacter::Open_Inventory);
	PlayerInputComponent->BindAction("Open Inventory", IE_Released, this, &AThe_VisionCharacter::Close_Inventory);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AThe_VisionCharacter::Start_Zooming);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AThe_VisionCharacter::Stop_Zooming);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AThe_VisionCharacter::Start_Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AThe_VisionCharacter::Stop_Sprint);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AThe_VisionCharacter::Reload_Pressed);

	PlayerInputComponent->BindAction("Move_Forwards", IE_Pressed, this, &AThe_VisionCharacter::Move_ForwardPressed);
	PlayerInputComponent->BindAction("Move_Forwards", IE_Released, this, &AThe_VisionCharacter::Move_ForwardReleased);
	PlayerInputComponent->BindAction("Move_Backwards", IE_Pressed, this, &AThe_VisionCharacter::Move_BackwardPressed);
	PlayerInputComponent->BindAction("Move_Backwards", IE_Released, this, &AThe_VisionCharacter::Move_BackwardReleased);
	PlayerInputComponent->BindAction("Move_Right", IE_Pressed, this, &AThe_VisionCharacter::Move_RightPressed);
	PlayerInputComponent->BindAction("Move_Right", IE_Released, this, &AThe_VisionCharacter::Move_RightReleased);
	PlayerInputComponent->BindAction("Move_Left", IE_Pressed, this, &AThe_VisionCharacter::Move_LeftPressed);
	PlayerInputComponent->BindAction("Move_Left", IE_Released, this, &AThe_VisionCharacter::Move_LeftReleased);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AThe_VisionCharacter::TouchStarted);
	if (!EnableTouchscreenMovement(PlayerInputComponent))
	{
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AThe_VisionCharacter::OnFirePressed);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &AThe_VisionCharacter::OnFireReleased);
	}

	/*PlayerInputComponent->BindAxis("MoveForward", this, &AThe_VisionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThe_VisionCharacter::MoveRight);*/

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThe_VisionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThe_VisionCharacter::LookUpAtRate);
}


void AThe_VisionCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AThe_VisionCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFirePressed();
	}
	TouchItem.bIsPressed = false;
}

//void AThe_VisionCharacter::MoveForward(float Value)
//{
//	if (Value != 0.0f)
//	{
//		// add movement in that direction
//		AddMovementInput(GetActorForwardVector(), Value);
//	}
//}

//void AThe_VisionCharacter::MoveRight(float Value)
//{
//	if (Value != 0.0f)
//	{
//		// add movement in that direction
//		AddMovementInput(GetActorRightVector(), Value);
//	}
//}

void AThe_VisionCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThe_VisionCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AThe_VisionCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AThe_VisionCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AThe_VisionCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AThe_VisionCharacter::TouchUpdate);
	}
	return bResult;
}

void AThe_VisionCharacter::OnFirePressed()
{
	bLeftMousePressed = true;
}

void AThe_VisionCharacter::OnFireReleased()
{
	bLeftMousePressed = false;
	StartTimer = false;
}

void AThe_VisionCharacter::Start_Zooming()
{
	float Current_Zoom = FirstPersonCamera->FieldOfView;

	float InFieldOfView = UKismetMathLibrary::FInterpTo(Current_Zoom, 60, 10, 0.1);

	FirstPersonCamera->SetFieldOfView(InFieldOfView);
}

void AThe_VisionCharacter::Stop_Zooming()
{
	FirstPersonCamera->SetFieldOfView(camera_zoom);
}

void AThe_VisionCharacter::Start_Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = run_speed;
}

void AThe_VisionCharacter::Stop_Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walk_speed;
}

void AThe_VisionCharacter::Reload_Pressed()
{
	FTimerHandle TimeHandle;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &AThe_VisionCharacter::Reload, Reload_Delay);
}

void AThe_VisionCharacter::Reload()
{
	Rifle_Ammo = 30;

}

void AThe_VisionCharacter::Move_Forward()
{
	float Value = 1.0f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AThe_VisionCharacter::Move_Backward()
{
	float Value = -1.0f;
	AddMovementInput(GetActorForwardVector(), Value);

}

void AThe_VisionCharacter::Move_Left()
{
	float Value = -1.0f;
	AddMovementInput(GetActorRightVector(), Value);
}

void AThe_VisionCharacter::Move_Right()
{
	float Value = 1.0f;
	AddMovementInput(GetActorRightVector(), Value);
}

void AThe_VisionCharacter::Move_ForwardPressed()
{
	bMoveForwardPressed = true;
}

void AThe_VisionCharacter::Move_ForwardReleased()
{
	bMoveForwardPressed = false;
}

void AThe_VisionCharacter::Move_BackwardPressed()
{
	bMoveBackwardPressed = true;
}

void AThe_VisionCharacter::Move_BackwardReleased()
{
	bMoveBackwardPressed = false;
}

void AThe_VisionCharacter::Move_LeftPressed()
{
	bMoveLeftPressed = true;
}

void AThe_VisionCharacter::Move_LeftReleased()
{
	bMoveLeftPressed = false;
}

void AThe_VisionCharacter::Move_RightPressed()
{
	bMoveRightPressed = true;
}

void AThe_VisionCharacter::Move_RightReleased()
{
	bMoveRightPressed = false;
}

void AThe_VisionCharacter::Open_Inventory()
{
	//bInvPressed = true;
	if (W_Inventory)
	{

		inventory_widget = CreateWidget<UUserWidget>(GetWorld(), W_Inventory);
		if (inventory_widget)
		{
			inventory_widget->AddToViewport();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("AD"));
}

void AThe_VisionCharacter::Close_Inventory()
{
	inventory_widget->RemoveFromParent();
}


void AThe_VisionCharacter::ReportNoise(USoundBase * SoundToPlay, float Volume)
{
	if (SoundToPlay)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation(), Volume);

		MakeNoise(Volume, this, GetActorLocation());
	}
}

// Fire Raycast
void AThe_VisionCharacter::Fire(float LineTraceLenght, ECollisionChannel CollisionChannel)
{
	if (Rifle_Ammo > 0)
	{
		//location the PC is focused on
		const FVector Start = FirstPersonCamera->GetComponentLocation();

		//LineTraceLenght in facing direction of PC 
		const FVector End = Start + (FirstPersonCamera->GetForwardVector() * LineTraceLenght);

		//The trace data is stored here
		FHitResult HitOut;


		bool ReturnPhysMat = false;
		AEnemy_Character* Enemy;


		if (UWorld* World = GetWorld())
		{
			if (UStatic_Libary::LineTrace(World, Start, End, HitOut, CollisionChannel, ReturnPhysMat))
			{
				if (HitOut.GetActor()->ActorHasTag("Enemy"))
				{

					Enemy = Cast<AEnemy_Character>(HitOut.GetActor());
					Enemy->SetLife(30);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Getroffen"));
				}

				if (HitOut.GetActor() != NULL)
				{
					DoDamage(HitOut);
					//SpawnBulletHole(HitOut);
				}
			}
			UGameplayStatics::PlaySoundAtLocation(World, FireSound, HitOut.TraceStart);
			Rifle_Ammo--;
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LEER"));
	}


	StartTimer = false;
}


void AThe_VisionCharacter::SpawnBulletHole(FHitResult const& HitOut)
{
	FVector Decal_Size = FVector(1, 1, 1);

	FVector Decal_Location = HitOut.Location;
	FRotator Decal_Rotation = UKismetMathLibrary::FindLookAtRotation(HitOut.Location, HitOut.Location + HitOut.Normal);
	FActorSpawnParameters Decal_Spawn_Params;

	UWorld* TempWorld = GetWorld();
	AActor* Spawned_Decal = TempWorld->SpawnActor<AActor>(Bullet_Hole_Decal, Decal_Location, FRotator(), Decal_Spawn_Params);

	Spawned_Decal->SetActorRotation(Decal_Rotation);
}

void AThe_VisionCharacter::DoDamage(FHitResult const& HitOut)
{
	FVector Force_Vector = HitOut.TraceEnd - HitOut.TraceStart;
	Force_Vector.Normalize();
	if (HitOut.GetActor() != NULL)
	{

		if (HitOut.GetActor()->ActorHasTag("Monitor"))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Monitor_BreakGlass_Sound, HitOut.Location);
		}

		UPrimitiveComponent* Hit_Component = HitOut.GetComponent();
		//Hit_Component->AddImpulse(Force_Vector * Normal_Force, NAME_None, true);

		if (ADestructibleActor* HitActor = Cast<ADestructibleActor>(HitOut.GetActor()))
		{
			if (HitActor->ActorHasTag("Cube"))
			{
				//HitActor->GetDestructibleComponent()->AddImpulse(Force_Vector * Destructible_Force, NAME_None, false);
				UGameplayStatics::ApplyRadialDamage(GetWorld(), 30.0f, HitOut.Location, 15.0f, UDestructible_DamageType::StaticClass(), TArray<AActor*>(), this);
				//HitActor->GetDestructibleComponent()->ApplyDamage(10.0f, HitOut.Location, HitOut.Location, 50.0f);
			}
		}
	}
}

// Open Door
void AThe_VisionCharacter::Interact()
{
	float LineTraceLenght = 200;

	//location the PC is focused on
	const FVector Start = FirstPersonCamera->GetComponentLocation();

	//LineTraceLenght in facing direction of PC 
	const FVector End = Start + (FirstPersonCamera->GetForwardVector() * LineTraceLenght);

	//The trace data is stored here
	FHitResult Item_HitOut;

	ECollisionChannel CollisionChannel = ECC_GameTraceChannel2;

	bool ReturnPhysMat = false;
	if (UWorld* world = GetWorld())
	{
		//DrawDebugLine(world, Start, End, FColor::Green, true, 10, 0, 2.f);
		if (UStatic_Libary::LineTrace(world, Start, End, Item_HitOut, CollisionChannel, ReturnPhysMat))
		{
			if (Item_HitOut.Actor->GetClass()->ImplementsInterface(UActivationInterface::StaticClass()))
			{
				if (IActivationInterface* ActivationObject = dynamic_cast<IActivationInterface*, AActor>(&*Item_HitOut.Actor))
				{
					ActivationObject->Activate();
				}
				else
				{
					IActivationInterface::Execute_BPEvent_Activate(&*Item_HitOut.Actor);
				}
			}
		}
		if (UStatic_Libary::LineTrace(world, Start, End, Item_HitOut, CollisionChannel, ReturnPhysMat))
		{
			if (Item_HitOut.GetActor()->ActorHasTag("Item"))
			{
				Inventory_Manager->AddItemtoList(Item_HitOut.GetActor());
				Item_HitOut.GetActor()->Destroy();
			}
		}
	}
}

void AThe_VisionCharacter::FindInventoryManager()
{
	for (TActorIterator<AInventory_Manager> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		Inventory_Manager = *ActorIt;
	}
}

//bool AThe_VisionCharacter::ResetFirstShootTimer(float deltatime)
//{
//	TapDelay += deltatime * 1000;
//	GLog->Log(FString::SanitizeFloat(deltatime));
//	if (TapDelay > TapTimer)
//	{
//		TapDelay = 0;
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//
//}
//
//bool AThe_VisionCharacter::Tapping(float deltatime)
//{
//	TapDelay += deltatime;
//	GLog->Log(FString::SanitizeFloat(TapDelay));
//	if (TapDelay >= .08f && TapDelay <= .75f)
//	{
//		float OutValue = FMath::Lerp(.1f, .75f, TapDelay / .75f);
//
//		if (OutValue <= 1.0f)
//		{
//			TapDelay = 0;
//			return true;
//		}
//		else
//		{
//			//TapDelay = 0;
//
//			return false;
//		}
//	}
//	else
//	{
//
//		return false;
//	}
//
//}