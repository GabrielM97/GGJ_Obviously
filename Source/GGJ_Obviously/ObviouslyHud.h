// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombinationLockWidget.h"
#include "ObviouslyHud.generated.h"

class UPlayerHud;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLockUIUpdate, UCombinationLockWidget*);

/**
 * 
 */
UCLASS()
class GGJ_OBVIOUSLY_API AObviouslyHud : public AHUD
{
	GENERATED_BODY()

public:

	AObviouslyHud();
	
	UPROPERTY(EditAnywhere, Category=PlayerHud)
	TSubclassOf<UPlayerHud> PlayerHudClass;

	UPROPERTY(EditAnywhere, Category = "PlayerHud")
	TSubclassOf<UCombinationLockWidget> CombinationLockUIClass;

	UPROPERTY()
	UPlayerHud* PlayerHud;

	UPROPERTY()
	UCombinationLockWidget* CombinationLockWidget;
	
	FOnLockUIUpdate LockUIUpdate;

	void SetInteractText(const FText& text);
	void ToggleInteractUI(ESlateVisibility Visibility);

	void ToggleCombinationLockUI();

protected:
	virtual void BeginPlay() override;
};
