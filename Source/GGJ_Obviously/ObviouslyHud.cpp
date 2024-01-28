// Fill out your copyright notice in the Description page of Project Settings.


#include "ObviouslyHud.h"
#include "PlayerHud.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

AObviouslyHud::AObviouslyHud()
{

}

void AObviouslyHud::SetInteractText(const FText& text)
{
	PlayerHud->InteractionText->SetText(text);
}

void AObviouslyHud::ToggleInteractUI(ESlateVisibility Visibility)
{
	PlayerHud->InteractionText->SetVisibility(Visibility);
}

void AObviouslyHud::ToggleCombinationLockUI()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	if (!IsValid(CombinationLockWidget))
	{
		return;
	}
	
	if (!CombinationLockWidget->IsInViewport())
	{
		CombinationLockWidget->AddToViewport(10);
		const FInputModeUIOnly UIOnly;
		PlayerController->SetInputMode(UIOnly);
		PlayerController->SetShowMouseCursor(true);
	}
	else
	{
		CombinationLockWidget->RemoveFromParent();
		const FInputModeGameOnly GameOnly;
		PlayerController->SetInputMode(GameOnly);
		PlayerController->SetShowMouseCursor(true);
	}
}

void AObviouslyHud::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetOwningPlayerController();

	if (!IsValid(PlayerController) || !IsValid(PlayerHudClass))
	{
		return;
	}
	
	PlayerHud = CreateWidget<UPlayerHud>(PlayerController, PlayerHudClass);
	PlayerHud->AddToViewport();

	CombinationLockWidget = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUIClass);
	CombinationLockWidget->Owner = PlayerController;
}
