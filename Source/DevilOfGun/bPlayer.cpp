// Fill out your copyright notice in the Description page of Project Settings.


#include "bPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AbPlayer::AbPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("bPlayerSkeletal"));;
	RootComponent = Mesh;

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->TargetOffset = FVector(0.0f, 0.0f, 0.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AbPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AbPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AbPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AbPlayer::AddControllerRollInput(float Val)
{
	Super::AddControllerRollInput(Val);
}

void AbPlayer::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val);
}

void AbPlayer::Delay()
{
	FireDelay = false;
}

void AbPlayer::Fire()
{
	if (ProjectileClass && Ammo != 0 && !FireDelay)
	{
		FireDelay = true;

		FVector CameraLocation;
		FRotator CameraRotation;
		CameraLocation = GetActorLocation();
		CameraRotation = Mesh->GetRelativeRotation();

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Yaw += 90.0f;
		MuzzleRotation.Pitch -= Mesh->GetRelativeRotation().Roll;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
		Ammo -= 1;
		//GetWorld()->GetTimerManager().SetTimer(timer_fire, this, &AbPlayer::Fire, 0.1f, true);
		GetWorld()->GetTimerManager().SetTimer(timer_delay, this, &AbPlayer::Delay, 0.3f, false);
	}
}

void AbPlayer::isFire()
{
	isFiring = true;
	Fire();
}

void AbPlayer::stopFire()
{
	isFiring = false;
}