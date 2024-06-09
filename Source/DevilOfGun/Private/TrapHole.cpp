// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapHole.h"
#include "DevilOfGun/aPlayer.h"
#include "DevilOfGun/DevilOfGunGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
ATrapHole::ATrapHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("bullet box componenet"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ATrapHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapHole::OnTrapOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	AaPlayer* player = Cast<AaPlayer>(OtherActor);

	if (player != nullptr) {
		ADevilOfGunGameModeBase* currentGameModeBase = Cast<ADevilOfGunGameModeBase>(GetWorld()->GetAuthGameMode());
		currentGameModeBase->ShowDieWidget();
	}
}