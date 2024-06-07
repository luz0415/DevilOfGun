// Fill out your copyright notice in the Description page of Project Settings.


#include "Kraken.h"
#include "KrakenWeakness.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "IDamagable.h"
#include "../aPlayer.h"

AKraken::AKraken()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Enemy/Boss/ABP_Kraken.ABP_Kraken_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	attackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	attackBox->SetupAttachment(GetMesh());
	attackBox->SetCollisionProfileName("NoCollision");

	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	attackBox->SetBoxExtent(boxSize);
	attackBox->OnComponentBeginOverlap.AddDynamic(this, &AKraken::OnOverlapAttackBox);
}

void AKraken::BeginPlay()
{
	Super::BeginPlay();

	bIsAttackBegun = false;
	bIsTurning = false;
	bIsAttackSpecial = false;
	bIsAttacking = false;
}

void AKraken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsAttackBegun) 
	{
		if(!attackReadyTimer.IsValid())
			GetWorld()->GetTimerManager().SetTimer(attackReadyTimer, this, &AKraken::AttackReady, 5.0f, false);
	}
	else 
	{
		if (bIsTurning) 
		{
			Turn();
		}
		else if(!bIsAttacking)
		{
			if (bIsAttackSpecial)
			{
				UE_LOG(LogTemp, Warning, TEXT("Special Attack"));
				GetWorld()->GetTimerManager().SetTimer(specialAttackTimer, this, &AKraken::SpecialAttack, 10.0f, false);
			}
			else 
			{
				BaseAttack();
				//GetWorld()->GetTimerManager().SetTimer(attackTimer, this, &AKraken::BaseAttack, 1.0f, false);
			}
		}
	}

}

void AKraken::CreateWeaknesses(int count)
{
	TArray<int32> randNums;

	for (int32 i = 0; i < count; ++i)
	{
		int32 rand;
		do
		{
			rand = FMath::RandRange(1, 11);
		} while (randNums.Contains(rand));
		randNums.Add(rand);
	}

	for (int i = 0; i < count; i++) 
	{
		int randomIndex = randNums[i];
		FName socketName = FName("WeaknessSocket" + FString::FromInt(randomIndex));
		UKrakenWeakness* newWeakness = GetWorld()->SpawnActor<UKrakenWeakness>(weaknessMeshComp, GetActorLocation(), GetActorRotation());
		newWeakness->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
		weaknesses.Add(newWeakness);
	}
}

void AKraken::HitWeakness(UKrakenWeakness* weakness)
{
	weaknesses.Remove(weakness);
	weakness->DestroyComponent();
	if (weaknesses.Num() == 0)
	{
		HitAllWeaknesses();
	}
}

void AKraken::HitAllWeaknesses()
{
	GetWorld()->GetTimerManager().ClearTimer(specialAttackTimer);
	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(GetHitMontage, 1.0f);
		FOnMontageEnded GetHitEnd;
		GetHitEnd.BindLambda([this](UAnimMontage* Montage, bool bInterrupted) { bIsTurning = bIsAttackBegun = bIsAttacking = false; });
		AnimInstance->Montage_SetEndDelegate(GetHitEnd, GetHitMontage);
	}
}

void AKraken::OnOverlapAttackBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("HitActor: %s"), *(OtherActor->GetFName()).ToString());
	IIDamagable* damagable = Cast<IIDamagable>(OtherActor);
	if (damagable && player == Cast<AActor>(damagable))
	{
		damagable->TakeDamage(attackDamage);
	}
}

void AKraken::AttackReady()
{
	bIsAttackBegun = true;
	bIsTurning = true;
	bIsAttackSpecial = CanSpecialAttack();
	if(bIsAttackSpecial)
	{
		int weaknessCount = (3 - (nextSpeicalAttackHP / 25)) * 2;
		CreateWeaknesses(weaknessCount);
		targetAngle = 90;
	}
	else
	{
		player = GetWorld()->GetFirstPlayerController()->GetPawn();
		FVector2D targetLocation = FVector2D(player->GetActorLocation().X, player->GetActorLocation().Y);
		FVector2D currentLocation = FVector2D(GetActorLocation().X, GetActorLocation().Y);

		FVector2D direction = targetLocation - currentLocation;
		targetAngle = -90 + FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X));
		if(targetAngle < 0)
		{
			targetAngle += 360;
		}
	}
}

void AKraken::SpecialAttack()
{
	bIsAttacking = true;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(SpecialAttackMontage, 1.0f);
		FOnMontageEnded AttackEnd;
		AttackEnd.BindLambda([this](UAnimMontage* Montage, bool bInterrupted) { bIsAttackBegun = bIsAttacking = false; });
		AnimInstance->Montage_SetEndDelegate(AttackEnd, SpecialAttackMontage);
	}
}

bool AKraken::CanSpecialAttack()
{
	if (currentHP <= nextSpeicalAttackHP)
	{
		nextSpeicalAttackHP -= 25;
		return true;
	}
	return false;
}

void AKraken::BaseAttack()
{
	bIsAttacking = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		AnimInstance->Montage_Play(AttackMontage, 1.0f);
		
		FOnMontageEnded AttackEnd;
		AttackEnd.BindLambda([this](UAnimMontage* Montage, bool bInterrupted) {
			UE_LOG(LogTemp, Warning, TEXT("Attack Montage End")); GetWorld()->GetTimerManager().ClearTimer(attackReadyTimer); bIsAttackBegun = bIsAttacking = false; });
		AnimInstance->Montage_SetEndDelegate(AttackEnd, AttackMontage);
	}
}

void AKraken::AttackHitCheck()
{
	attackBox->SetCollisionProfileName("Enemy");
	FTimerHandle overlapTimer;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]()
	{
			attackBox->SetCollisionProfileName("NoCollision");
	});
	GetWorld()->GetTimerManager().SetTimer(overlapTimer, TimerDelegate, 0.5f, false);
}

void AKraken::Turn()
{
	FRotator targetRotation = FRotator(0, targetAngle, 0);
	FRotator newRotation = FMath::RInterpTo(GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 1.0f);

	float angleDifference = FMath::Abs((newRotation - targetRotation).Yaw);
	if (angleDifference < 3.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turning Done"));
		bIsTurning = false;
	}

	SetActorRotation(newRotation);
}
