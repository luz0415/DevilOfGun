// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSp.h"
#include "Item.h"
#include "DevilOfGun/DevilOfGunGameModeBase.h"

// Sets default values
AItemSp::AItemSp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSp::BeginPlay()
{
	Super::BeginPlay();
	
	AItem* itemSpawn = GetWorld()->SpawnActor<AItem>(itemFactory[FMath::RandRange(0, 2)], this->GetActorLocation(), this->GetActorRotation());
	Destroy();
}

// Called every frame
void AItemSp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

