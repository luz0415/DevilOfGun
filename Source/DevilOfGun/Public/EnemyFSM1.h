// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM1.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEVILOFGUN_API UEnemyFSM1 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM1();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	// 대기 상태
	void IdleState();
	// 이동 상태
	void MoveState();
	// 공격 상태
	void AttackState();
	// 피격 상태
	void DamageState();
	// 죽음 상태
	void DieState();


	// 대기 시간
	
	UPROPERTY(EditAnywhere, Category = FSM)
	float idleDelayTime = 1;
	// 경과 시간
	float currentTime = 0;

	//플레이어
	UPROPERTY(EditAnywhere, Category = FSM)
	class AaPlayer* target; 
	UPROPERTY()
	//적(자신)
	class AEnemy1* me;
	//공격 범위
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 150.0f;
	//공격 대기시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 1.0f;

	float hp = 5;
	// 피격 대기 시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 0.5f;

	//사망 하강속도
	UPROPERTY(EditAnywhere, Category = FSM)
	float dieSpeed = 50.0f;

	UPROPERTY()
	class UEani* anim;
};
