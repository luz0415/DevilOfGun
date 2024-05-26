// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "aPlayer.generated.h"

UENUM()
enum class EPlayerType : uint8 {
	TE_OptionA UMETA(DisplayName = "Idle"),
	TE_OptionB UMETA(DisplayName = "Move"),
	TE_OptionC UMETA(DisplayName = "Sprint"),
	TE_OptionD UMETA(DisplayName = "Jump"),
	TE_OptionE UMETA(DisplayName = "Die"),
};

UCLASS()
class DEVILOFGUN_API AaPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AaPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float moveSpeed;

	UPROPERTY(EditAnywhere)
	float sprintMoveSpeed;

	UPROPERTY(EditAnywhere)
	EPlayerType playerAnimType;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* body;

	UPROPERTY(EditAnywhere)
	UArrowComponent* watchingArrow;

	UFUNCTION(BlueprintCallable, Category = "FuctionTest")
	EPlayerType GetPlayerType() { return playerAnimType; }

	// Camera Section
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	void SetMoveHorizontal(float value);
	void JumpStart();
	void AnimCtrl();
	void SprintStart();
	void SprintEnd();

	bool isSprint = false;
	float moveRightValue;
};
