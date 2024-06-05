// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Components/CapsuleComponent.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	currentHP = maxHP;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::OnDeath()
{
	Destroy();
}

void AMonster::TakeDamage(float damage)
{
	currentHP -= damage;
	if (currentHP <= 0)
	{
		OnDeath();
	}
}

void AMonster::RestoreHP(float restoreVal)
{
	currentHP += restoreVal;
	if (currentHP > maxHP)
	{
		currentHP = maxHP;
	}
}

