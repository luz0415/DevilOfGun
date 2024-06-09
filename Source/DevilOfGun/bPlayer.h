// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSProjectile.h"
#include "Components/SkeletalMeshComponent.h"
#include "bPlayer.generated.h"

UCLASS()
class DEVILOFGUN_API AbPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AbPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerRollInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;
	
	void Fire();
	void isFire();
	void stopFire();
	void Delay();

	FTimerHandle timer_delay;
	FTimerHandle timer_fire;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "GamePlay")
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AFPSProjectile> ProjectileClass;

	int Max_Ammo = 50;
	int Ammo = Max_Ammo;

	bool isFiring = false;
	bool FireDelay = false;
	bool ReLoding = false;

// Camera Section
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

private:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Mesh;
};
