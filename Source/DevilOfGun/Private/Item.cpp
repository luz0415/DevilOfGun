// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "DevilOfGun/aPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("bullet box componenet"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnItemOverlap);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {
	AaPlayer* player = Cast<AaPlayer>(OtherActor);

	if (player != nullptr) {
		switch(itemType) {
			case 0 :
				player->hp += 50;
				Destroy();
				break;
			case 1:
				player->bPlayerAttacked = false;
				Destroy();
				break;
			case 2:
				player->score += 50;
				Destroy();
				break;
			case 3:
				player->bPlayerAttacked = true;
				player->hp -= 100;
				Destroy();
				break;
			case 4:
				if (GetWorld()->GetMapName().Contains("Stage_1")) {
					UGameplayStatics::OpenLevel(GetWorld(), "Stage_2");
				}
				else if (GetWorld()->GetMapName().Contains("Stage_2")) {
					UGameplayStatics::OpenLevel(GetWorld(), "BossStage");
				}
				break;
		}
	}
}