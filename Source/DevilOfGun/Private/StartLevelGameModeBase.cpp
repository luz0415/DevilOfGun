// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"
#include "LevelSequencePlayer.h"

void AStartLevelGameModeBase::StartPlay()
{
    Super::StartPlay();
    FStringAssetReference SequenceName("/Game/Maps/MatineeActorLevelSequence.MatineeActorLevelSequence");
    ULevelSequence* Asset = Cast<ULevelSequence>(SequenceName.TryLoad());
    ALevelSequenceActor* LevelSequenceActor;
    SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(this, Asset, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);
    SequencePlayer->Play();

    if (dialogueWidget != nullptr) {
        dialogueUI = CreateWidget<UDialogueWidget>(GetWorld(), dialogueWidget);

        if (dialogueUI != nullptr) {
            dialogueUI->AddToViewport();
            dialogueUI->AddDialogue(FString(TEXT("서기 2238년, 강력하면서도 비인도적인 대량 살상 무기들을 개발하기 시작한 나라 '아미드'는 이를 활용해 주변 국가들을 빠르게 점령해나간다.")), 0);
            dialogueUI->AddDialogue(FString(TEXT("'아미드'는 멈추지 않고 계속해서 주변 국가들을 공격하고, 그동안의 평화에 안주하던 국가들은 '아미드'의 강력한 신무기에 대항하지 못하고 황폐화되어간다.")), 210);
            dialogueUI->AddDialogue(FString(TEXT("결국 패전국들의 잔당들은 모여서 저항군을 결성, '아미드'가 심혈을 기울여 개발 중인 신무기를 훔쳐 전세를 뒤집기로 결정한다. 이에 코드네임 '오클루트'는 신무기를 훔치기 위한 특수부대의 정예 요원으로서 무기 연구실을 잠입하게 된다.")), 660);
            dialogueUI->AddDialogue(FString(TEXT("'오클루트'는 특수 신소재로 만들어져 파괴되지 않고 자율적으로 적을 제거하는 특수살인병기 'Devil Of Gun', 일명 DOG를 획득하게 된다.")), 1089);
            dialogueUI->AddDialogue(FString(TEXT("하지만 동시에 경보가 울리며 '오클루트'를 제거하기 위해 적들이 몰려오기 시작하는데...")), 1365);
            dialogueUI->NextDialogue();
        }
    }
}

void AStartLevelGameModeBase::CompleteOrSkipDialogue()
{
    if (dialogueUI != nullptr) {
		dialogueUI->CompleteOrSkipDialogue();
	}
}

void AStartLevelGameModeBase::SkipFrame(int32 frameNumber)
{
    if (SequencePlayer != nullptr) {
        FFrameTime frame = FFrameTime(frameNumber);
		SequencePlayer->JumpToFrame(frame);
	}
}

void AStartLevelGameModeBase::ResumeSequencer()
{
    if (SequencePlayer != nullptr) {
		SequencePlayer->Play();
	}
}
