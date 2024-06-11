// Fill out your copyright notice in the Description page of Project Settings.


#include "Eani.h"
#include "../aPlayer.h"

void UEani:: OnEndAttackAnimation()
{
	attackplay = false;
}


void UEani::OnAttackPlay()
{
	auto actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	target = Cast<AaPlayer>(actor);
	
	target->TakeDamage(20);
	//여기 player 데미지 감소 함수
}

