// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevilOfGunGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API ADevilOfGunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	int32 playerHp = 100;
	int32 score = 0;
	int32 playerMaxHp = 100;
	float currentHp;
	class UmainWidget* mainUI;
	class UdieWidget* dieUi;

	void PrintMainUi();
	
public:
	ADevilOfGunGameModeBase();

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> aPlayer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> bPlayer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerController> aPlayerController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerController> bPlayerController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UmainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdieWidget> dieWidget;

	void ShowDieWidget();

	void PlayerChangeHp(int32 IPlayerHp);
	void ChaneScore(int32 currentScore);
	void changeHp(float hp);
	void SetPlayerHpBarControl(bool check);
};
