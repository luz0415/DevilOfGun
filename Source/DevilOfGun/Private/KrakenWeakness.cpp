// Fill out your copyright notice in the Description page of Project Settings.


#include "KrakenWeakness.h"
#include "Kraken.h"

UKrakenWeakness::UKrakenWeakness()
{
	currentHP = maxHP;
}

void UKrakenWeakness::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UKrakenWeakness::OnOverlapWeakness);
}

void UKrakenWeakness::TakeDamage(float damage)
{
	currentHP -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Weakness HP: %f"), currentHP);
	if (currentHP <= 0)
	{
		AKraken* owner = Cast<AKraken>(GetOwner());
		if (owner)
		{
			owner->HitWeakness(this);
		}
	}
}

void UKrakenWeakness::OnOverlapWeakness(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HitWeakness Overlap With: %s"), *(OtherActor->GetFName()).ToString());
}
