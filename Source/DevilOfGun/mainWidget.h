#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "mainWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API UmainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, meta = ( BindWidget ))
		class UTextBlock* scoreText;

	UPROPERTY(EditAnyWhere, meta = (BindWidget))
		class UTextBlock* bossNameData;

	UPROPERTY(EditAnyWhere, meta = (BindWidget))
		class UProgressBar* EnemyProgressBar;
};
