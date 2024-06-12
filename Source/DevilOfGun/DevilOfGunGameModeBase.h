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
	FString enemyCurrentName = "";
	float enemyCurrentHp;
	float enemyCurrentMaxHp;
	class UmainWidget* mainUI;
	class UdieWidget* dieUi;

	class APlayerController* aPlayerController;
	class APlayerController* bPlayerController;

	void PrintMainUi();
	
public:
	ADevilOfGunGameModeBase();

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> aPlayer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> bPlayer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UmainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdieWidget> dieWidget;

	void ShowDieWidget();

	void PlayerChangeHp(int32 IPlayerHp);
	void ChaneScore(int32 currentScore);
	void SetPlayerHpBarControl(bool check);
	void CloseWidget();
	void SetCameraOne();
	void EnemyAttacked(FString hitName, float enemyHp, float enemyMaxHp);
};
