// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DialogueHelper.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_OBVIOUSLY_API UDialogueHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDialogue(const FName Name);
	
};
