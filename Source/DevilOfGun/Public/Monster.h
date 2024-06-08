// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamagable.h"
#include "Monster.generated.h"

UCLASS()
class DEVILOFGUN_API AMonster : public ACharacter, public IIDamagable
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay() override;

// HP Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
	float maxHP = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float currentHP;

	virtual void OnDeath();

public:
	virtual void TakeDamage(float damage) override;
	virtual void RestoreHP(float restoreVal);
};
