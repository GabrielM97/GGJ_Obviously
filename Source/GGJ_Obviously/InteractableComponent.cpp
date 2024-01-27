// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"

#include "GGJ_ObviouslyCharacter.h"
#include "TriggerableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInteractableComponent::Interact(const AGGJ_ObviouslyCharacter* PlayerCharacter, UPrimitiveComponent* Comp, const FVector& HitLocation, const FRotator& HitRotation)
{
	switch (InteractionType) {
	case EInteractionType::EPickup:
		PlayerCharacter->PhysicsHandle->GrabComponentAtLocationWithRotation(Comp, NAME_None,  HitLocation, HitRotation);
		bIsActive = true;
		break;
		
	case EInteractionType::EPress:
		for (auto triggerable : Triggerables)
		{
			if (triggerable->GetClass()->ImplementsInterface(UTriggerableInterface::StaticClass())) {
				ITriggerableInterface::Execute_Activate(triggerable);
			}
		}
		bIsActive = true;
		break;
		
	case EInteractionType::EPressRandom:
		if (!Triggerables.IsEmpty())
		{
			const auto Triggerable = Triggerables[FMath::RandRange(0, Triggerables.Num() -1)];

			if (Triggerable->GetClass()->ImplementsInterface(UTriggerableInterface::StaticClass())) {
				ITriggerableInterface::Execute_Activate(Triggerable);
			}
		}

		break;
	}


}

// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

