// Copyright Epic Games, Inc. All Rights Reserved.


#include "GGJ_ObviouslyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ObviouslyHud.h"

void AGGJ_ObviouslyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	Hud = Cast<AObviouslyHud>(GetHUD());
}
