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

	void changeHp(float hp);
};
