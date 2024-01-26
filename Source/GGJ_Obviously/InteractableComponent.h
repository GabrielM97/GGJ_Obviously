// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class AGGJ_ObviouslyCharacter;
class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_OBVIOUSLY_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();
	void Interact(const AGGJ_ObviouslyCharacter* PlayerCharacter, UPrimitiveComponent* Comp, const FVector& HitLocation, const FRotator& HitRotation);

	UPROPERTY()
	UWidgetComponent* InteractWidget;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
