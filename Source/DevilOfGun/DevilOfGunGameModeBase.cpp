// Copyright Epic Games, Inc. All Rights Reserved.


#include "DevilOfGunGameModeBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "aPlayerController.h"
#include "bPlayerController.h"

ADevilOfGunGameModeBase::ADevilOfGunGameModeBase()
{
	DefaultPawnClass = nullptr;


}

void ADevilOfGunGameModeBase::StartPlay()
{
    Super::StartPlay();
    UGameplayStatics::SetPlayerControllerID(Cast<AaPlayerController>(aPlayerController), 0);
    UGameplayStatics::SetPlayerControllerID(Cast<AbPlayerController>(bPlayerController), 1);
    UGameInstance* GameInstance = GetGameInstance();

    APlayerController* A = GetWorld()->GetFirstPlayerController();
    APawn* aPlayerInGame = GetWorld()->SpawnActor<APawn>(aPlayer, FVector(0, 0, 0), FRotator(0, 0, 0));
    if (A)
    {
		A->Possess(aPlayerInGame);
	}

    APlayerController* B = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
    APawn* bPlayerInGame = GetWorld()->SpawnActor<APawn>(bPlayer, FVector(50, 0, 100), FRotator(0, 0, 0));
    bPlayerInGame->AttachToActor(aPlayerInGame, FAttachmentTransformRules::KeepRelativeTransform);
    if (B)
    {
		B->Possess(bPlayerInGame);
	}
}
