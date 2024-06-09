// Fill out your copyright notice in the Description page of Project Settings.


#include "aPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DevilOfGun/DevilOfGunGameModeBase.h"
#include "TimerManager.h"
#include "bPlayer.h"

// Sets default values
AaPlayer::AaPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletal"));
	body->SetupAttachment(RootComponent);

	watchingArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("WatchingArrow"));
	watchingArrow->SetupAttachment(RootComponent);

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	JumpMaxHoldTime = 0.5f;
}

// Called when the game starts or when spawned
void AaPlayer::BeginPlay()
{
	Super::BeginPlay();

	tmpHP = hp;
}

// Called every frame
void AaPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetPlayerType();
	FVector moveDir = FVector(0, moveRightValue, 0);
	moveDir.Normalize();

	FVector newLocation = GetActorLocation() + moveDir * (isSprint ? sprintMoveSpeed : moveSpeed) * DeltaTime;
	AnimCtrl();

	SetActorLocation(newLocation, true);

	fTimerStart = GetWorldTimerManager().IsTimerActive(bPlayerAttackedHandle);

	if (fTimerStart == false && bPlayerAttacked == false) {
		GetWorldTimerManager().SetTimer(bPlayerAttackedHandle, this, &AaPlayer::ResetbPlayerAttacked, skillDuration, true);
		ADevilOfGunGameModeBase* currentGameModeBase = Cast<ADevilOfGunGameModeBase>(GetWorld()->GetAuthGameMode());
		currentGameModeBase->SetPlayerHpBarControl(true);
	}
	ControlHp();
	ControScore();
}

// Called to bind functionality to input
void AaPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AaPlayer::SetMoveHorizontal);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AaPlayer::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AaPlayer::JumpStop);
	PlayerInputComponent->BindAction("APlayerFire", IE_Pressed, this, &AaPlayer::APlayerFireStart);
	PlayerInputComponent->BindAction("APlayerFire", IE_Released, this, &AaPlayer::APlayerFireEnd);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AaPlayer::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AaPlayer::SprintEnd);
	
	PlayerInputComponent->BindAxis("LookUp", this, &AaPlayer::AddbPlayerRollInput);
	PlayerInputComponent->BindAxis("Turn", this, &AaPlayer::AddbPlayerYawInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AaPlayer::Fire_A);
}

void AaPlayer::SetMoveHorizontal(float value) {
	moveRightValue = value;

	if (value < 0) {
		body->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}

	else if(value > 0) {
		body->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AaPlayer::SprintStart() {
	isSprint = true;
}
void AaPlayer::SprintEnd() {
	isSprint = false;
}

void AaPlayer::AddbPlayerRollInput(float Val)
{
	bPlayer->AddControllerRollInput(Val);
}

void AaPlayer::AddbPlayerYawInput(float Val)
{
	bPlayer->AddControllerYawInput(Val);
}

void AaPlayer::Fire_A()
{
	hp -= 10;
	bPlayer->Fire();
}

void AaPlayer::ResetbPlayerAttacked() {
	bPlayerAttacked = true;
	GetWorldTimerManager().ClearTimer(bPlayerAttackedHandle);
	ADevilOfGunGameModeBase* currentGameModeBase = Cast<ADevilOfGunGameModeBase>(GetWorld()->GetAuthGameMode());
	currentGameModeBase->SetPlayerHpBarControl(false);
}


void AaPlayer::JumpStart() {
	bPressedJump = true;
}
void AaPlayer::JumpStop() {
	bPressedJump = false;
}

void AaPlayer::APlayerFireStart() {
	isFire = true;
}

void AaPlayer::APlayerFireEnd() {
	isFire = false;
	fireCount = 1;
}

void AaPlayer::AnimCtrl() {
	if (moveRightValue != 0 && !isSprint) {
		playerAnimType = EPlayerType::TE_OptionB;
	}

	else if (moveRightValue != 0 && isSprint) {
		playerAnimType = EPlayerType::TE_OptionC;
	}

	else if (isFire && !isSprint) {
		playerAnimType = EPlayerType::TE_OptionD;
	}

	else if (moveRightValue == 0) {
		playerAnimType = EPlayerType::TE_OptionA;
	}
}

void AaPlayer::ControScore() {
	if (score != tmpScore) {
		tmpScore = score;
		ADevilOfGunGameModeBase* currentGameModeBase = Cast<ADevilOfGunGameModeBase>(GetWorld()->GetAuthGameMode());
		currentGameModeBase->ChaneScore(score);
	}
}

void AaPlayer::ControlHp() {
	if (hp != tmpHP) {
		if (bPlayerAttacked == true) {
			tmpHP = hp;
			ADevilOfGunGameModeBase* currentGameModeBase = Cast<ADevilOfGunGameModeBase>(GetWorld()->GetAuthGameMode());
			if (hp <= 0) {
				currentGameModeBase->ShowDieWidget();
				Destroy();
			}
			else {
				currentGameModeBase->PlayerChangeHp(hp);
			}
		}
		else {
			hp = tmpHP;
		}
	}
}