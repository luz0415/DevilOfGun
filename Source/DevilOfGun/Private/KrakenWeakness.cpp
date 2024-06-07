// Fill out your copyright notice in the Description page of Project Settings.


#include "KrakenWeakness.h"
#include "Kraken.h"

UKrakenWeakness::UKrakenWeakness()
{
	currentHP = maxHP;
}

void UKrakenWeakness::TakeDamage(float damage)
{
	currentHP -= damage;
	if (currentHP <= 0)
	{
		AKraken* owner = Cast<AKraken>(GetOwner());
		if (owner)
		{
			owner->HitWeakness(this);
		}
	}
}
