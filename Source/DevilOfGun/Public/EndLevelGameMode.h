// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API AEndLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	void CompleteOrSkipDialogue();
	void SkipFrame(int32 frame);
	void ResumeSequencer();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDialogueWidget> dialogueWidget;

private:
	class UDialogueWidget* dialogueUI;
	class ULevelSequencePlayer* StartSequencePlayer;

public:
	void SkipCinematic();
};
