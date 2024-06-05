// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API AStartLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;
	void CompleteOrSkipDialogue();
	void SkipFrame(int32 frame);
	void ResumeSequencer();

	UPROPERTY(EditAnywhere)	
	TSubclassOf<class UDialogueWidget> dialogueWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULobbyWidget> lobbyWidget;

private:
	class UDialogueWidget* dialogueUI;
	class ULobbyWidget* lobbyUI;
	class ULevelSequencePlayer* StartSequencePlayer;
	class ULevelSequencePlayer* LobbySequencePlayer;

public:
	void SkipCinematic();
};
