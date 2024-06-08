// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamagable.h"
#include "Enemy1.generated.h"

UCLASS()
class DEVILOFGUN_API AEnemy1 : public ACharacter, public IIDamagable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* body;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UEnemyFSM1* fsm;

	UPROPERTY(EditAnywhere)
	float hp = 5;
	UPROPERTY(EditAnywhere)
	FString name = "basic";

	virtual void TakeDamage(float damage) override;
};
