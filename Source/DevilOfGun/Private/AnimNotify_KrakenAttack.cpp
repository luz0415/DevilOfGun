// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_KrakenAttack.h"
#include "Kraken.h"
void UAnimNotify_KrakenAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp) 
	{
		AKraken* Kraken = Cast<AKraken>(MeshComp->GetOwner());
		if (Kraken) 
		{
			Kraken->AttackHitCheck();
		}
	}
}
