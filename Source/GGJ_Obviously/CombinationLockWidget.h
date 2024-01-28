// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombinationLockWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCombinationAttempt, bool, IsSuccessful, UUserWidget*, Widget);

/**
 * 
 */
UCLASS()
class GGJ_OBVIOUSLY_API UCombinationLockWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintCallable)
	FOnCombinationAttempt CombinationAttempt;
};
