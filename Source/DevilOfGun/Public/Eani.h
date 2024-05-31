// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Eani.generated.h"

/**
 * 
 */
UCLASS()
class DEVILOFGUN_API UEani : public UAnimInstance
{
	GENERATED_BODY()
public:
	// 플레이어 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;
};
