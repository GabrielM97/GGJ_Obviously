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

void UCombinationLockComponent::OnCombinationAttempt(bool IsSuccesful, UUserWidget* WidgetUI)
{
	if (IsSuccesful) 
	{
		WidgetUI->RemoveFromParent();
	}
}


// Called when the game starts
void UCombinationLockComponent::BeginPlay()
{
	Super::BeginPlay();

	UInteractableComponent* Interactable = Cast<UInteractableComponent>(GetOwner()->GetComponentByClass(UInteractableComponent::StaticClass()));
	
	// if (auto world = GetWorld())
	// {
	// 	auto characterController = static_cast<AGGJ_ObviouslyPlayerController*>(world->GetFirstPlayerController());
	// 	if (characterController) 
	// 	{
	// 		characterController->Hud->LockUIUpdate.AddUObject(this, &UCombinationLockComponent::SubscribeToDelegate);
	// 	}
	// }

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
		characterController->Hud->LockUIUpdate.AddUObject(this, &UCombinationLockComponent::SubscribeToDelegate);
		characterController->Hud->ToggleCombinationLockUI();
	}
}
	

void UCombinationLockComponent::SubscribeToDelegate(UCombinationLockWidget* WidgetUI)
{
	WidgetUI->CombinationAttempt.AddDynamic(this, &UCombinationLockComponent::OnCombinationAttempt);
}
