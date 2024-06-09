// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "Kraken.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API AKraken : public AMonster
{
	GENERATED_BODY()
	
public:
	AKraken();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	class AActor* player;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* attackBox;

	UFUNCTION()
	void OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// Anim Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* SpecialAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* GetHitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* DieMontage;

public:
	virtual void TakeDamage(float damage) override;
	void AttackHitCheck();

protected:
	uint8 bIsDead : 1;
	virtual void OnDeath() override;

private:
	class ULevelSequencePlayer* KrakenDieSequencePlayer;

// Weakness Section
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UKrakenWeakness> weaknessMeshComp;
	TArray<class UKrakenWeakness*> weaknesses;

	void CreateWeaknesses(int count);
	void HitAllWeaknesses();
public:
	void HitWeakness(class UKrakenWeakness* weakness);

// Attack Section
private:
	UPROPERTY(EditAnywhere)
	float attackDamage = 15;
	
	uint8 bIsWeaknessExist : 1;
	uint8 bIsAttackBegun : 1;
	uint8 bIsTurning : 1;
	uint8 bIsAttacking : 1;

	FTimerHandle attackReadyTimer;
	FTimerHandle attackTimer;

	UFUNCTION()
	void AttackReady();
	UFUNCTION()
	void BaseAttack();

// Special Attack Section
private:
	uint8 bIsAttackSpecial : 1;
	FTimerHandle specialAttackTimer;
	
	UFUNCTION()
	void SpecialAttack();
	float nextSpeicalAttackHP = 75;
	bool CanSpecialAttack();

// Turn Section
private:
	FTimerHandle TurnTimer;
	void Turn();
	float targetAngle;
};
