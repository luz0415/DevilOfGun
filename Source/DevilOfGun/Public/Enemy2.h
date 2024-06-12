// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamagable.h"
#include "Enemy2.generated.h"

UCLASS()
class DEVILOFGUN_API AEnemy2 : public AActor, public IIDamagable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere)
	float hp = 10;
	UPROPERTY(EditAnywhere)
	float maxHp = 10;
	UPROPERTY(EditAnywhere)
	int e2type = 0;
	UPROPERTY(EditAnywhere)
	FString name = "enemy2";
	float moveSpeed = 300;

	float h=0, v=0;
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	UPROPERTY(EditAnywhere) //움직임 지속시간 조절
	float dt[2] = { 1,1 };
	float timer = 0;
	float timer2 = 0;
	virtual void TakeDamage(float damage) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEbullet> bulletFactory;

	//플레이어
	UPROPERTY(EditAnywhere)
	class AaPlayer* target;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponet, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

