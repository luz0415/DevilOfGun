// Fill out your copyright notice in the Description page of Project Settings.

#include "Ebullet.h"
#include "../aPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AEbullet::AEbullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static mesh"));
	meshComp->SetupAttachment(boxComp);
	FVector boxSize = FVector(50, 50, 50);
	boxComp->SetBoxExtent(boxSize);

	boxComp->SetCollisionProfileName(TEXT("Bullet"));


}

// Called when the game starts or when spawned
void AEbullet::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEbullet::OnHit);
}

// Called every frame
void AEbullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEbullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponet, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AaPlayer* aplayer = Cast<AaPlayer>(OtherActor);
	if (aplayer != nullptr)
	{
		//플레이어 hp 감소
	}

	this->Destroy();

}