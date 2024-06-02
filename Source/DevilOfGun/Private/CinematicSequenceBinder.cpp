// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicSequenceBinder.h"
#include "StartLevelGameModeBase.h"

ACinematicSequenceBinder::ACinematicSequenceBinder()
{

}

void ACinematicSequenceBinder::NextDialogueWhenSequenceIsFinished()
{
	GetWorld()->GetAuthGameMode<AStartLevelGameModeBase>()->CompleteOrSkipDialogue();
}
void ACinematicSequenceBinder::BeginPlay()
{
	Super::BeginPlay();

}