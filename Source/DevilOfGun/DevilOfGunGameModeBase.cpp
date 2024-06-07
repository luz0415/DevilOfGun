// Copyright Epic Games, Inc. All Rights Reserved.


#include "DevilOfGunGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "aPlayer.h"
#include "bPlayer.h"

ADevilOfGunGameModeBase::ADevilOfGunGameModeBase()
{
	DefaultPawnClass = nullptr;
}

void ADevilOfGunGameModeBase::StartPlay()
{
    Super::StartPlay();
    //UGameplayStatics::SetPlayerControllerID(Cast<AaPlayerController>(aPlayerController), 0);
    //UGameplayStatics::SetPlayerControllerID(Cast<AaPlayerController>(bPlayerController), 1);

    APlayerController* A = GetWorld()->GetFirstPlayerController();
    AaPlayer* aPlayerInGame = GetWorld()->SpawnActor<AaPlayer>(aPlayer, FVector(0, 0, 0), FRotator(0, 0, 0));
    if (A)
    {
		A->Possess(aPlayerInGame);
	}

    APlayerController* B = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

    AbPlayer* bPlayerInGame = GetWorld()->SpawnActor<AbPlayer>(bPlayer, FVector(30, 45, 125), FRotator(0, 0, 0));
    bPlayerInGame->AttachToActor(aPlayerInGame, FAttachmentTransformRules::KeepRelativeTransform);
    aPlayerInGame->bPlayer = bPlayerInGame;
    if (B)
    {
		B->Possess(bPlayerInGame);
        B->InitInputSystem();
	}

    if (mainWidget != nullptr) {
        mainUI = CreateWidget<UmainWidget>(GetWorld(), mainWidget);

        if (mainUI != nullptr) {
            mainUI->AddToViewport();
        }
    }
}

void ADevilOfGunGameModeBase::PrintMainUi() {
    if (mainUI != nullptr) {
        mainUI->playerHpBar->SetPercent(((float)playerHp / (float)playerMaxHp));
        mainUI->playerHpText->SetText(FText::AsNumber(playerHp));
    }
}

void ADevilOfGunGameModeBase::PlayerChangeHp(int32 IPlayerHp) {
    playerHp = IPlayerHp;
    PrintMainUi();
}
