// Fill out your copyright notice in the Description page of Project Settings.


#include "bPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AbPlayer::AbPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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


void AbPlayer::Fire()
{
	if (ProjectileClass)
	{
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
	}
}

