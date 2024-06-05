// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyFSM1.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Eani.generated.h"

UCLASS()
class DEVILOFGUN_API UEani : public UAnimInstance
{
	GENERATED_BODY()
public:
	// 플레이어 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	EEnemyState animState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool attackplay= false;
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
	void OnEndAttackAnimation();
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
	void AttackPlay();

	UPROPERTY(EditAnywhere, Category = FSM)
	class AaPlayer* target;
};
