#pragma once

#include "Dialogue.generated.h"
class USoundCue;

USTRUCT(BlueprintType)
struct FDialogue :  public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> DialogueTexts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<USoundCue*> SpokenDialogue;
};
