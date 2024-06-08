// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy2.h"
#include "Ebullet.h"
#include "../aPlayer.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AEnemy2::AEnemy2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static mesh"));
	meshComp->SetupAttachment(sphereComp);
	sphereComp->InitSphereRadius(50.f);
	sphereComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemy2::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy2::OnHit);
}

// Called every frame
void AEnemy2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (hp <= 0) Destroy();

	FVector dir = FVector(0, h, v);;

	if (e2type == 0) {
		int d = int(timer);
		d %= 4;
		timer += dt[d%2] * DeltaTime;;
		h = dx[d];
		v = dy[d];
		dir = FVector(0, h, v);
	}
	else if (e2type == 1) {
		int d = int(timer);
		d %= 4;
		timer += dt[d % 2] * DeltaTime;;
		h = dx[d];
		v = dy[d];
		dir = FVector(h, 0, v);
	}
	else if (e2type == 2) {
		timer += 1 * DeltaTime;
		auto actor = GetWorld()->GetFirstPlayerController()->GetPawn();
		target = Cast<AaPlayer>(actor);
		FVector Dir = (target->GetActorLocation()- GetActorLocation()).GetSafeNormal();
		SetActorRotation(Dir.Rotation());

		if (timer >= 1) {
			timer = 0;

			AEbullet* ebullet = GetWorld()->SpawnActor<AEbullet>(bulletFactory, GetActorLocation(), GetActorRotation());
		}
	}



	dir.Normalize();
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;
	SetActorLocation(newLocation, true);

}

void AEnemy2::TakeDamage(float damage)
{
	hp -= damage;

}


void AEnemy2::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponet, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	AaPlayer* aplayer = Cast<AaPlayer>(OtherActor);
	if (aplayer != nullptr)
	{
		//플레이어 hp 감소
	}
	//Destroy();
}