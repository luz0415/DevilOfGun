// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "StartLevelGameModeBase.h"
#include "EndLevelGameMode.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
	dialogueIndex = -1;
	dialogueText->Text = FText::FromString("");
	nextButton->OnClicked.AddDynamic(this, &UDialogueWidget::CompleteOrSkipDialogue);

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void UDialogueWidget::AddDialogue(const FString& dialogue, int32 startFrame)
{
	dialogues.Add(dialogue);
	dialogueStartFrames.Add(startFrame);
}

void UDialogueWidget::ClearDialogue()
{
	dialogues.Empty();
}

void UDialogueWidget::NextDialogue()
{
	GetWorld()->GetTimerManager().ClearTimer(letterTimer);
	GetWorld()->GetTimerManager().ClearTimer(mouseImgTimer);
	dialogueIndex++;
	letterIndex = 0;
	if (dialogues.Num() > 0 && dialogues.Num() > dialogueIndex)
	{
		AStartLevelGameModeBase* gameMode = Cast<AStartLevelGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->SkipFrame(dialogueStartFrames[dialogueIndex]);
			gameMode->ResumeSequencer();
		}

		AEndLevelGameMode* endGameMode = Cast<AEndLevelGameMode>(GetWorld()->GetAuthGameMode());
		if (endGameMode != nullptr)
		{
			endGameMode->SkipFrame(dialogueStartFrames[dialogueIndex]);
			endGameMode->ResumeSequencer();
		}

		mouseImage->SetVisibility(ESlateVisibility::Hidden);
		bIsDialogueFinished = false;
		dialogueText->SetText(FText::FromString(""));
		GetWorld()->GetTimerManager().SetTimer(letterTimer, this, &UDialogueWidget::NextLetter, letterSpeed, true);
	}	
	else if (dialogueIndex == dialogues.Num())
	{
		AStartLevelGameModeBase* gameMode = Cast<AStartLevelGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->SkipCinematic();
			return;
		}

		AEndLevelGameMode* endGameMode = Cast<AEndLevelGameMode>(GetWorld()->GetAuthGameMode());
		if (endGameMode != nullptr)
		{
			endGameMode->SkipCinematic();
			return;
		}
	}
}

void UDialogueWidget::CompleteOrSkipDialogue()
{
	if(bIsDialogueFinished)
	{
		NextDialogue();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(letterTimer);
		dialogueText->SetText(FText::FromString(dialogues[dialogueIndex]));
		GetWorld()->GetTimerManager().SetTimer(letterTimer, this, &UDialogueWidget::BlinkMouseImage, mosueImgSpeed, true);
		bIsDialogueFinished = true;
	}
}

void UDialogueWidget::NextLetter()
{
	FString currentDialogue = dialogues[dialogueIndex];
	if (letterIndex < dialogues[dialogueIndex].Len())
	{
		FString currentLetter = currentDialogue.Mid(letterIndex, 1);
		dialogueText->SetText(FText::FromString(dialogueText->GetText().ToString() + currentLetter));
		letterIndex++;
	}
	else
	{
		CompleteOrSkipDialogue();
	}
}

void UDialogueWidget::BlinkMouseImage()
{
	if (mouseImage->GetVisibility() == ESlateVisibility::Visible)
	{
		mouseImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		mouseImage->SetVisibility(ESlateVisibility::Visible);
	}
}
