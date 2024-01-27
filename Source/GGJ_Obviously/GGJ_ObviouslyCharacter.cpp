// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ_ObviouslyCharacter.h"
#include "GGJ_ObviouslyProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GGJ_ObviouslyPlayerController.h"
#include "InputActionValue.h"
#include "InteractableComponent.h"
#include "ObviouslyHud.h"
#include "Components/SlateWrapperTypes.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGGJ_ObviouslyCharacter

AGGJ_ObviouslyCharacter::AGGJ_ObviouslyCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

void AGGJ_ObviouslyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	World = GetWorld();
	PC = static_cast<AGGJ_ObviouslyPlayerController*>( World->GetFirstPlayerController());
}

//////////////////////////////////////////////////////////////////////////// Input

void AGGJ_ObviouslyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGGJ_ObviouslyCharacter::Interact);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGGJ_ObviouslyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGGJ_ObviouslyCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGGJ_ObviouslyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FRotator CameraRot = FirstPersonCameraComponent->GetComponentRotation();
	FVector Forward = UKismetMathLibrary::GetForwardVector(CameraRot);
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + Forward * 250;

	if (World)
	{
		World->LineTraceSingleByChannel(Out, Start, End, ECC_Visibility);
		
		if (!IsValid(PC))
		{
			return;
		}
		
		if (Out.bBlockingHit)
		{
			InteractableComponent = Cast<UInteractableComponent>(Out.GetActor()->GetComponentByClass(UInteractableComponent::StaticClass()));
			
			if (!IsValid(InteractableComponent))
			{
				return;
			}

			if (!bIsGrabbing && !InteractableComponent->bIsActive)
			{
				PC->Hud->SetInteractText( FText::FromString(FString::Printf(TEXT("Press 'E' to interact with %s"), *Out.GetActor()->GetName())));
				PC->Hud->ToggleInteractUI(ESlateVisibility::SelfHitTestInvisible);
			}
		}
		else
		{
			PC->Hud->ToggleInteractUI(ESlateVisibility::Collapsed);
			InteractableComponent = nullptr;
		}
	}
	
	if(bIsGrabbing)
	{
		PhysicsHandle->SetTargetLocationAndRotation(End, CameraRot);
	}
}

void AGGJ_ObviouslyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGGJ_ObviouslyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGGJ_ObviouslyCharacter::Interact()
{
	if (!InteractableComponent || !Out.bBlockingHit)
	{
		return;
	}

	if (bIsGrabbing)
	{
		PhysicsHandle->ReleaseComponent();
		InteractableComponent=nullptr;
		bIsGrabbing = false;
		return;
	}
	
	InteractableComponent->Interact(this, Out.GetComponent(), Out.GetComponent()->GetComponentLocation(), Out.GetComponent()->GetComponentRotation());
	PC->Hud->ToggleInteractUI(ESlateVisibility::Collapsed);
	bIsGrabbing =  IsValid(PhysicsHandle->GrabbedComponent);
}

void AGGJ_ObviouslyCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGGJ_ObviouslyCharacter::GetHasRifle()
{
	return bHasRifle;
}