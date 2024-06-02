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

	UPROPERTY(EditAnywhere)	
	TSubclassOf<class UDialogueWidget> dialogueWidget;

private:
	class UDialogueWidget* dialogueUI;
};
