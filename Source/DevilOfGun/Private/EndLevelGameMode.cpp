// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelGameMode.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"

void AEndLevelGameMode::StartPlay()
{
    Super::StartPlay();
    FStringAssetReference SequenceName("/Game/Levels/CinematicSequence.CinematicSequence");
    ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());
    ALevelSequenceActor* LevelSequenceActor;
    StartSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, Asset, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);
    StartSequencePlayer->Play();

    if (dialogueWidget != nullptr) {
        dialogueUI = CreateWidget<UDialogueWidget>(GetWorld(), dialogueWidget);

        if (dialogueUI != nullptr) {
            dialogueUI->AddToViewport();
            dialogueUI->AddDialogue(FString(TEXT("'오클루트'는 치열한 전투 끝에 '아미드'의 경계를 뚫고 탈출에 성공한다.")), 0);
            dialogueUI->AddDialogue(FString(TEXT("황폐해진 도시를 지나며 저항군의 비밀 기지에 도착한 그는, 'DOG'를 안전하게 전달하고 자신이 임무를 완수했음을 알린다.")), 210);
            dialogueUI->AddDialogue(FString(TEXT("저항군은 '오클루트'의 용기와 희생에 경의를 표하며, 이 신무기를 통해 '아미드'에 대항할 수 있는 새로운 희망을 얻게 된다.")), 660);
            dialogueUI->AddDialogue(FString(TEXT("'오클루트'는 깊은 숨을 내쉬며, 자신이 세상을 바꾸는 데 기여했다는 뿌듯함과 함께 동료들과의 재회를 기뻐한다.")), 1089);
            dialogueUI->AddDialogue(FString(TEXT("마침내, '오클루트'는 동료들과 함께 더 나은 미래를 향해 나아가기로 결심한다.")), 1365);
            dialogueUI->NextDialogue();
        }
    }
}

void AEndLevelGameMode::CompleteOrSkipDialogue()
{
	if (dialogueUI != nullptr) {
		dialogueUI->CompleteOrSkipDialogue();
	}
}

void AEndLevelGameMode::SkipFrame(int32 frame)
{
	if (StartSequencePlayer != nullptr) {
		FFrameTime frameTime = FFrameTime(frame);
		StartSequencePlayer->JumpToFrame(frameTime);
	}
}

void AEndLevelGameMode::ResumeSequencer()
{
	if (StartSequencePlayer != nullptr) {
		StartSequencePlayer->Play();
	}
}

void AEndLevelGameMode::SkipCinematic()
{
    if (StartSequencePlayer != nullptr) {
		StartSequencePlayer->Stop();
	}

    if (dialogueUI != nullptr) {
        dialogueUI->RemoveFromViewport();
    }

    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Cinematic_Start"));
}
