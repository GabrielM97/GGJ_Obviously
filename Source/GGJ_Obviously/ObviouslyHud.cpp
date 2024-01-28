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
	
	if (CombinationLockUI) 
	{
		if (CombinationLockUI.Get()->GetIsVisible())
		{
			CombinationLockUI = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUI.Get()->StaticClass());
			auto UIWidget = CombinationLockUI.Get(); 
			UIWidget->Initialize();
			UIWidget->AddToViewport();
			LockUIUpdate.Broadcast(UIWidget);
		}
		else
		{
			if (CombinationLockUI) 
			{
				CombinationLockUI.Get()->RemoveFromParent();
			}
		}
	}
	else 
	{
		CombinationLockUI = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUI.Get()->StaticClass());
		auto UIWidget = CombinationLockUI.Get();
		UIWidget->Initialize();
		UIWidget->AddToViewport();
		LockUIUpdate.Broadcast(UIWidget);
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

	CombinationLockUI = CreateWidget<UCombinationLockWidget>(PlayerController, CombinationLockUI.Get()->StaticClass());
	auto UIWidget = CombinationLockUI.Get();
	UIWidget->AddToViewport();
	LockUIUpdate.Broadcast(UIWidget);
}
