// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM1.h"
#include "../aPlayer.h"
#include "Enemy1.h"
#include "Eani.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h> 

// Sets default values for this component's properties
UEnemyFSM1::UEnemyFSM1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM1::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AaPlayer::StaticClass());
	auto actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	target = Cast<AaPlayer>(actor);
	// ���� ��ü ��������
	me = Cast<AEnemy1>(GetOwner());
	anim=Cast<UEani>(me->body->GetAnimInstance());

}


// Called every frame
void UEnemyFSM1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (me->hp != hp) {
		hp = me->hp;
		currentTime = 0;
		mState = EEnemyState::Damage;
	}

	switch (mState) {
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}
void UEnemyFSM1::IdleState() {
	anim->animState = mState;
	currentTime += GetWorld()->DeltaTimeSeconds;
	// �ʹ� ���ð�
	if (currentTime > idleDelayTime)
	{
		if (target == NULL) {
			auto actor = GetWorld()->GetFirstPlayerController()->GetPawn();
			target = Cast<AaPlayer>(actor);
			// �ʹ� ���ð� �ʱ�ȭ
			idleDelayTime = -1;
		}
		FVector destination = target->GetActorLocation();
		FVector dir = destination - me->GetActorLocation();
		if (dir.Size() < attackRange * 3)
		{
			mState = EEnemyState::Move;
			

		}
		// ��� �ð� �ʱ�ȭ

		currentTime = 0;
	}


}
// �̵� ����
void UEnemyFSM1::MoveState() {
	anim->animState = mState;
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());
	if (dir.Size() < attackRange)
	{
		anim->attackplay = false;
		currentTime = 0.9;
		mState = EEnemyState::Attack;

	}
	else if (dir.Size() > attackRange * 3)
	{
		mState = EEnemyState::Idle;
	}
}
// ���� ����
void UEnemyFSM1::AttackState() {
	anim->animState = mState;
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		//attack
		anim->attackplay = true;
		currentTime = 0;
		anim->animState = mState;
	}
	// Ÿ����� �Ÿ�
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
	}
}
// �ǰ� ����
void UEnemyFSM1::DamageState() {
	anim->animState = mState;
	if (hp <= 0)
		mState = EEnemyState::Die;

	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime) {
		mState = EEnemyState::Idle;
		currentTime = 0;
	}
}
// ���� ����
void UEnemyFSM1::DieState() {
	anim->animState = mState;
	me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// ��ӿ ���� P = PO + vt

	FVector PO = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = PO + vt;
	me->SetActorLocation(P);
	if (P.Z < -200.f) {
		me->Destroy();
	}
}