// Fill out your copyright notice in the Description page of Project Settings.


#include "CombinationLockComponent.h"
#include "GGJ_ObviouslyPlayerController.h"

// Sets default values for this component's properties
UCombinationLockComponent::UCombinationLockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombinationLockComponent::OnCombinationAttempt(bool IsSuccesful, UCombinationLockWidget* WidgetUI)
{
	if (IsSuccesful) 
	{
		UInteractableComponent* Interactable = Cast<UInteractableComponent>(GetOwner()->GetComponentByClass(UInteractableComponent::StaticClass()));

		if (Interactable)
		{
			Interactable->OnInteracted.Clear();
			Interactable->InteractionType = EInteractionType::EPickup;
			Interactable->bIsActive = false;
		}
	}
}

// Called when the game starts
void UCombinationLockComponent::BeginPlay()
{
	Super::BeginPlay();

	UInteractableComponent* Interactable = Cast<UInteractableComponent>(GetOwner()->GetComponentByClass(UInteractableComponent::StaticClass()));

	if (Interactable) 
	{
		Interactable->OnInteracted.AddUObject(this, &UCombinationLockComponent::OpenLockUI);
	}
}

void UCombinationLockComponent::OpenLockUI(FInteractionData Data)
{
	auto world = GetWorld();
	if (!world) 
	{
		return;
	}

	if (const auto characterController = static_cast<AGGJ_ObviouslyPlayerController*>(world->GetFirstPlayerController())) 
	{
		characterController->Hud->ToggleCombinationLockUI();
		if (IsFirstOpen) 
		{
			characterController->Hud->CombinationLockWidget->CombinationAttempt.AddDynamic(this, &UCombinationLockComponent::OnCombinationAttempt);
			IsFirstOpen = false;
		}
	}
}
