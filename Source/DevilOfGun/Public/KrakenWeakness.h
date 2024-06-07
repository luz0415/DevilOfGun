// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "IDamagable.h"
#include "KrakenWeakness.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API UKrakenWeakness : public UStaticMeshComponent, public IIDamagable
{
	GENERATED_BODY()
public:
	UKrakenWeakness();

private:
	UPROPERTY(EditAnywhere)
	float maxHP = 3;
	float currentHP;

public:
	virtual void TakeDamage(float damage) override;
};
