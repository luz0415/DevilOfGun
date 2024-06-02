// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"

void AStartLevelGameModeBase::StartPlay()
{
    Super::StartPlay();
    if (dialogueWidget != nullptr) {
        dialogueUI = CreateWidget<UDialogueWidget>(GetWorld(), dialogueWidget);

        if (dialogueUI != nullptr) {
            dialogueUI->AddToViewport();
            dialogueUI->AddDialogue(FString("Hello, I am the Devil of Gun. I will guide you through this game."));
            dialogueUI->AddDialogue(FString("You will be playing as the character on the left side of the screen."));
            dialogueUI->AddDialogue(FString("Use the arrow keys to move and the space bar to shoot."));
            dialogueUI->AddDialogue(FString("Your goal is to defeat the enemy on the right side of the screen."));
            dialogueUI->AddDialogue(FString("Good luck!"));
            dialogueUI->NextDialogue();
        }
    }
}

void AStartLevelGameModeBase::CompleteOrSkipDialogue()
{
    if (dialogueUI != nullptr) {
		dialogueUI->CompleteOrSkipDialogue();
	}
}
