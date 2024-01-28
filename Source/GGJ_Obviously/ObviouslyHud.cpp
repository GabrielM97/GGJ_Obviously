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
		LockUIUpdate.Broadcast(CombinationLockWidget);
	}
	else
	{
		CombinationLockWidget->RemoveFromParent();
		const FInputModeGameOnly GameOnly;
		PlayerController->SetInputMode(GameOnly);
		PlayerController->SetShowMouseCursor(true);
	}
	
	
	// if (CombinationLockUI) 
	// {
	// 	if (CombinationLockUI.Get()->IsVisible())
	// 	{
	// 		// CombinationLockUI = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUI.Get()->StaticClass());
	// 		// auto UIWidget = CombinationLockUI.Get(); 
	// 		// UIWidget->Initialize();
	// 		CombinationLockUI.Get()->AddToViewport();
	// 		LockUIUpdate.Broadcast(CombinationLockUI.Get());
	// 	}
	// 	else
	// 	{
	// 		if (CombinationLockUI) 
	// 		{
	// 			CombinationLockUI.Get()->RemoveFromParent();
	// 		}
	// 	}
	// }
	// else 
	// {
	// 	// CombinationLockUI = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUI.Get()->StaticClass());
	// 	// auto UIWidget = CombinationLockUI.Get();
	// 	// UIWidget->Initialize();
	// 	CombinationLockUI.Get()->AddToViewport();
	// 	LockUIUpdate.Broadcast(CombinationLockUI.Get());
	// }
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
	// auto UIWidget = CombinationLockUI.Get();
	// UIWidget->AddToViewport();
	//LockUIUpdate.Broadcast(CombinationLockUI.Get());
}
