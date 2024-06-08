// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"
#include "Enemy1.h"
#include "EnemyFSM1.h"
#include "Enemy2.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 2500.0f;
	ProjectileMovementComponent->MaxSpeed = 2500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{ 
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSProjectile::OnHit);
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponet, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy1* Enemy1 = Cast<AEnemy1>(OtherActor);
	AEnemy2* Enemy2 = Cast<AEnemy2>(OtherActor);
	if (Enemy1 != nullptr)
	{
		Enemy1->TakeDamage(4);
	}
	else if (Enemy2 != nullptr) {
		Enemy2->TakeDamage(4);
	}

	Destroy();
}