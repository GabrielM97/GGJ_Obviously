// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GGJ_ObviouslyPlayerController.generated.h"

class UPhysicsHandleComponent;
class AObviouslyHud;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class GGJ_OBVIOUSLY_API AGGJ_ObviouslyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowInteractionUI();

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;


	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	

public:
	UPROPERTY()
	AObviouslyHud* Hud;
	
	// End Actor interface
};
