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
	float currentHp;
	class UmainWidget* mainUI;
<<<<<<< HEAD
	class UdieWidget* dieUi;

	void PrintMainUi();
=======
>>>>>>> parent of e99b560 (V0.2.4)
	
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

<<<<<<< HEAD
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdieWidget> dieWidget;

	void ShowDieWidget();

	void PlayerChangeHp(int32 playerHp);
=======
	void changeHp(float hp);
>>>>>>> parent of e99b560 (V0.2.4)
};
