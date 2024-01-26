// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ObviouslyHud.generated.h"

class UPlayerHud;
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

	UPROPERTY()
	UPlayerHud* PlayerHud;
protected:
	virtual void BeginPlay() override;
};
