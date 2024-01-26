// Fill out your copyright notice in the Description page of Project Settings.


#include "ObviouslyHud.h"
#include "PlayerHud.h"

#include "Blueprint/UserWidget.h"

AObviouslyHud::AObviouslyHud()
{

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
}
