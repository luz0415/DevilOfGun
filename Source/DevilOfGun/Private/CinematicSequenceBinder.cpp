// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicSequenceBinder.h"
#include "StartLevelGameModeBase.h"
#include "LevelSequenceActor.h"
ACinematicSequenceBinder::ACinematicSequenceBinder()
{

}

void ACinematicSequenceBinder::StopSequence(class ULevelSequencePlayer* SequencePlayer)
{
	SequencePlayer->Pause();
}
void ACinematicSequenceBinder::BeginPlay()
{
	Super::BeginPlay();

}