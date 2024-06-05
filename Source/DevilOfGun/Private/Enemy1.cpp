// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy1.h"
#include "EnemyFSM1.h"

// Sets default values
AEnemy1::AEnemy1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletal"));
	body->SetupAttachment(RootComponent);
	//fsm Ãß°¡
	fsm = CreateDefaultSubobject<UEnemyFSM1>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemy1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

