// Fill out your copyright notice in the Description page of Project Settings.


#include "Eani.h"
#include "../aPlayer.h"

void UEani:: OnEndAttackAnimation()
{
	attackplay = false;
}


void UEani::AttackPlay()
{
	auto actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	target = Cast<AaPlayer>(actor);
	target->Destroy();
}

