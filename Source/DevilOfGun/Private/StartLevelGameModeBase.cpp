// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"
#include "LevelSequencePlayer.h"

void AStartLevelGameModeBase::StartPlay()
{
    Super::StartPlay();
    FStringAssetReference SequenceName("/Game/Maps/MatineeActorLevelSequence.MatineeActorLevelSequence");
    ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());
    ALevelSequenceActor* LevelSequenceActor;
    SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, Asset, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);
    SequencePlayer->Play();

    if (dialogueWidget != nullptr) {
        dialogueUI = CreateWidget<UDialogueWidget>(GetWorld(), dialogueWidget);

        if (dialogueUI != nullptr) {
            dialogueUI->AddToViewport();
            dialogueUI->AddDialogue(FString("Hello, I am the Devil of Gun. I will guide you through this game."), 0);
            dialogueUI->AddDialogue(FString("You will be playing as the character on the left side of the screen."), 150);
            dialogueUI->AddDialogue(FString("Use the arrow keys to move and the space bar to shoot."), 630);
            dialogueUI->AddDialogue(FString("Your goal is to defeat the enemy on the right side of the screen."), 1200);
            dialogueUI->AddDialogue(FString("Good luck!"), 1350);
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

void AStartLevelGameModeBase::SkipFrame(int32 frameNumber)
{
    if (SequencePlayer != nullptr) {
        FFrameTime frame = FFrameTime(frameNumber);
		SequencePlayer->JumpToFrame(frame);
	}
}
