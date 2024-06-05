// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UButton* startButton;
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UButton* settingButton;
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	class UButton* exitButton;

	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void OpenSetting();
	UFUNCTION()
	void ExitGame();
};
