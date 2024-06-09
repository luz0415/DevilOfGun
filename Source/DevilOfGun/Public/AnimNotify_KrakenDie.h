// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_KrakenDie.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API UAnimNotify_KrakenDie : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
};
