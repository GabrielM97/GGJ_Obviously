// Copyright Epic Games, Inc. All Rights Reserved.

#include "GGJ_ObviouslyGameMode.h"
#include "GGJ_ObviouslyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGGJ_ObviouslyGameMode::AGGJ_ObviouslyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
