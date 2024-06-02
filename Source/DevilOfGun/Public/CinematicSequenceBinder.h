// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CinematicSequenceBinder.generated.h"

UCLASS()
class DEVILOFGUN_API ACinematicSequenceBinder : public AActor
{
	GENERATED_BODY()
	
public:	
	ACinematicSequenceBinder();
	UFUNCTION(BlueprintCallable)
	void NextDialogueWhenSequenceIsFinished();


protected:
	virtual void BeginPlay() override;


};
