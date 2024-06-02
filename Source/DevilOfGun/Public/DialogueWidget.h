// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void AddDialogue(const FString& dialogue, int32 startFrame);
	void ClearDialogue();
	void NextDialogue();
	UFUNCTION()
	void CompleteOrSkipDialogue();

private:
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UButton* nextButton;

	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UTextBlock* dialogueText;

	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UImage* mouseImage;

	uint8 bIsDialogueFinished : 1;
	TArray<FString> dialogues;
	TArray<int32> dialogueStartFrames;
	int32 dialogueIndex;

private:
	UPROPERTY(EditAnyWhere)
	float letterSpeed = 0.1f;

	FTimerHandle letterTimer;
	int32 letterIndex;
	void NextLetter();
};
