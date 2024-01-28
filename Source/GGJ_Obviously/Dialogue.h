#pragma once

#include "Dialogue.generated.h"
class USoundCue;

USTRUCT(BlueprintType)
struct FDialogue :  public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueTexts;

	UPROPERTY(EditAnywhere)
	TArray<USoundCue*> SpokenDialogue;
};
