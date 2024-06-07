// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	startButton->OnClicked.AddDynamic(this, &ULobbyWidget::StartGame);
	settingButton->OnClicked.AddDynamic(this, &ULobbyWidget::OpenSetting);
	exitButton->OnClicked.AddDynamic(this, &ULobbyWidget::ExitGame);
}

void ULobbyWidget::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameLevel"));
}

void ULobbyWidget::OpenSetting()
{
	// Open Setting Widget
}

void ULobbyWidget::ExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}
