// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_KrakenDie.h"

void UAnimNotify_KrakenDie::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		MeshComp->GetAnimInstance()->GetOwningComponent()->GlobalAnimRateScale = 0.0f;
	}
}
