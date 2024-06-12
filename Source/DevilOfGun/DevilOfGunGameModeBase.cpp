// Copyright Epic Games, Inc. All Rights Reserved.


#include "DevilOfGunGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"
#include "dieWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "aPlayer.h"
#include "bPlayer.h"
#include "Engine/LocalPlayer.h"

ADevilOfGunGameModeBase::ADevilOfGunGameModeBase()
{
	DefaultPawnClass = nullptr;
}

void ADevilOfGunGameModeBase::StartPlay()
{
    Super::StartPlay();
    UE_LOG(LogTemp, Warning, TEXT("StartPlay"));

    aPlayerController = GetWorld()->GetFirstPlayerController();
    AaPlayer* aPlayerInGame = GetWorld()->SpawnActor<AaPlayer>(aPlayer, FVector(0, 0, 0), FRotator(0, 0, 0));
    if (aPlayerController)
    {
        aPlayerController->Possess(aPlayerInGame);
    }

    if (GetNumPlayers() < 2) bPlayerController = UGameplayStatics::CreatePlayer(GetWorld(), 1, true);
    else bPlayerController = UGameplayStatics::GetPlayerController(this, 1);

    AbPlayer* bPlayerInGame = GetWorld()->SpawnActor<AbPlayer>(bPlayer, FVector(30, 45, 125), FRotator(0, 0, 0));
    bPlayerInGame->AttachToActor(aPlayerInGame, FAttachmentTransformRules::KeepRelativeTransform);
    aPlayerInGame->bPlayer = bPlayerInGame;
    if (bPlayerController)
    {
        bPlayerController->Possess(bPlayerInGame);
    }

    if (mainWidget != nullptr) {
        mainUI = CreateWidget<UmainWidget>(GetWorld(), mainWidget);

        if (mainUI != nullptr) {
            mainUI->AddToViewport();
        }
    }
}

void ADevilOfGunGameModeBase::ShowDieWidget() {
    if (dieWidget != nullptr) {
        dieUi = CreateWidget<UdieWidget>(GetWorld(), dieWidget);


        if (dieUi != nullptr) {
            mainUI->RemoveFromViewport();
            dieUi->AddToViewport();

            UGameplayStatics::SetGamePaused(GetWorld(), true);

            GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
        }
    }
}

void ADevilOfGunGameModeBase::PrintMainUi() {
    if (mainUI != nullptr) {
        mainUI->playerHpBar->SetPercent(((float)playerHp / (float)playerMaxHp));
        mainUI->playerHpText->SetText(FText::AsNumber(playerHp));
        mainUI->scoreText->SetText(FText::AsNumber(score));

        mainUI->EnemyProgressBar->SetPercent((float)(enemyCurrentHp) / (float)(enemyCurrentMaxHp));
        mainUI->bossNameData->SetText(FText::FromString(enemyCurrentName));
    }
}

void ADevilOfGunGameModeBase::ChaneScore(int32 currentScore) {
    score = currentScore;
    PrintMainUi();
}

void ADevilOfGunGameModeBase::PlayerChangeHp(int32 IPlayerHp) {
    playerHp = IPlayerHp;
    PrintMainUi();
}

void ADevilOfGunGameModeBase::SetPlayerHpBarControl(bool check) {
    if (check) {
        mainUI->playerHpBar->SetFillColorAndOpacity(FVector(1, 0, 1));
    }

    else {
        mainUI->playerHpBar->SetFillColorAndOpacity(FVector(1, 1, 1));
    }
    PrintMainUi();
}
void ADevilOfGunGameModeBase::CloseWidget()
{
    if (mainUI != nullptr) {
        mainUI->RemoveFromViewport();
	}
}

void ADevilOfGunGameModeBase::SetCameraOne()
{
    UGameplayStatics::RemovePlayer(bPlayerController, false);
}

void ADevilOfGunGameModeBase::EnemyAttacked(FString hitName, float enemyHp, float enemyMaxHp) {
    enemyCurrentHp = enemyHp;
    enemyCurrentName = hitName;
    enemyCurrentMaxHp = enemyMaxHp;
    PrintMainUi();
}