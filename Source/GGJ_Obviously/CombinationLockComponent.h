// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.h"
#include "ObviouslyHud.h"
#include "CombinationLockComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_OBVIOUSLY_API UCombinationLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombinationLockComponent();

	void OnCombinationAttempt(bool IsSuccesful, UUserWidget* WidgetUI);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenLockUI(FInteractionData Data);

	void SubscribeToDelegate(UCombinationLockWidget* WidgetUI);
};
