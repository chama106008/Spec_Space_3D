// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecSpace3D_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "SpecSpace3D_PlayerController.h"
#include "GameFramework/Character.h"
#include "SpecSpace3D_GameInstance.h"
#include "Sound/SoundBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpecSpace3D_GameMode::ASpecSpace3D_GameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

// -------------
// ヘルパー
// -------------
bool ASpecSpace3D_GameMode::SetInputUI()
{   
    // Pawnの操作停止、入力制限、カーソル表示
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC)
    {
        return false;
    }

    APawn* Pawn = PC->GetPawn();
    if (Pawn)
    {
        Pawn->DisableInput(PC);
    }

    PC->SetInputMode(FInputModeUIOnly());
    PC->bShowMouseCursor = true;

    return true;
}

bool ASpecSpace3D_GameMode::SetInputGame()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC)
    {
        return false;
    }

    APawn* Pawn = PC->GetPawn();
    if (Pawn)
    {
        Pawn->EnableInput(PC);
    }

    PC->SetInputMode(FInputModeGameOnly());
    PC->bShowMouseCursor = false;

    return true;

}

bool ASpecSpace3D_GameMode::SetInputBoth()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC)
    {
        return false;
    }

    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputMode.SetHideCursorDuringCapture(false);

    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = true;

    return true;

}

void ASpecSpace3D_GameMode::CountdownTick()
{
    CountdownTime--;

    if (CountdownTime <= 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);

        CurrentState = EGameState::Playing;
        SetInputGame();
        if (StageBGM)
        {
            UGameplayStatics::PlaySound2D(GetWorld(), StageBGM);
        }
        
    }
}



// -------------
// 通常処理
// -------------

void ASpecSpace3D_GameMode::BeginPlay()
{   
    Super::BeginPlay();

    CurrentState = EGameState::CountDown;
    
    // ゲームインスタンスから現在レベルの比較用データを取得
    auto* GI = GetGameInstance<USpecSpace3D_GameInstance>();
    if (!GI) return;
    FName LevelName = *GetWorld()->GetName();
    bool bNewRecord = false;
    // StageDataを更新
    for (FStageData& Stage : GI->AllStages)
    {
        if (Stage.LevelName == LevelName)
        {
            TimeLimit = Stage.TimeLimit;
        }
    }

    SetInputUI();
    RemainingTime = TimeLimit;
    ElapsedTime = 0.0f;
    

    CountdownTime = 3;

    //カウントダウンアニメーション再生
    if (CountDownBGM)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), CountDownBGM);
    }
    GetWorld()->GetTimerManager().SetTimer(
        CountdownAnimDelayHandle,
        [this]()
        {
            APlayerController* BasePC = UGameplayStatics::GetPlayerController(this, 0);
            ASpecSpace3D_PlayerController* PC = Cast<ASpecSpace3D_PlayerController>(BasePC);
            if (PC)
            {
                PC->StartCountDown();
            }

            GetWorld()->GetTimerManager().SetTimer(
                CountdownTimerHandle,
                this,
                &ASpecSpace3D_GameMode::CountdownTick,
                1.0f,
                true
            );
        },
        0.5f,
        false
    );

}

void ASpecSpace3D_GameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    //プレイ中の時間処理
    if (CurrentState == EGameState::Playing)
    {
        ElapsedTime += DeltaSeconds;
        RemainingTime -= DeltaSeconds;
        
        const int32 DisplayTime = FMath::CeilToInt(RemainingTime);

        if (DisplayTime != LastSentTime)
        {
            LastSentTime = DisplayTime;
            APlayerController* BasePC = UGameplayStatics::GetPlayerController(this, 0);
            ASpecSpace3D_PlayerController* PC = Cast<ASpecSpace3D_PlayerController>(BasePC);
            if (PC)
            {
                PC->UpdateTimer(LastSentTime);
            }
            
        }

        if (RemainingTime <= 0.0f)
        {
            RemainingTime = 0.0f;
            HandleGameOver();
        }
    }
}

// クリア時処理
void ASpecSpace3D_GameMode::HandleStageClear()
{   
    if (CurrentState != EGameState::Playing)
    {
        return;
    }

    CurrentState = EGameState::Cleared;
    SetInputUI();

    // 丸め
    float ClearTime = FMath::RoundToFloat(ElapsedTime * 100.0f) / 100.0f;

    // 以降そのまま使う

    // ゲームインスタンスから現在レベルの比較用データを取得
    auto* GI = GetGameInstance<USpecSpace3D_GameInstance>();
    if (!GI) return;
    FName LevelName = *GetWorld()->GetName();
    bool bNewRecord = false;
    // StageDataを更新
    for (FStageData& Stage : GI->AllStages)
    {
        if (Stage.LevelName == LevelName)
        {
            bNewRecord = (!Stage.bCleared || ClearTime < Stage.BestTime);

            Stage.bCleared = true;

            if (bNewRecord)
            {
                Stage.BestTime = ClearTime;
            }

            break;
        }
    }
    GI->BuildSaveDataFromStages();
    GI->SaveCurrentData();

    // controllerからUI処理を呼び出し
    APlayerController* BasePC = UGameplayStatics::GetPlayerController(this, 0);
    ASpecSpace3D_PlayerController* PC = Cast<ASpecSpace3D_PlayerController>(BasePC);
    if (PC)
    {
        PC->RequestStageClear(ClearTime, bNewRecord);
    }


}

// ゲームオーバー処理
void ASpecSpace3D_GameMode::HandleGameOver()
{   
    if (CurrentState != EGameState::Playing)
    {
        return;
    }

    CurrentState = EGameState::GameOver;
    SetInputUI();

    //controllerからUI処理を呼び出し
    APlayerController* BasePC = UGameplayStatics::GetPlayerController(this, 0);
    ASpecSpace3D_PlayerController* PC = Cast<ASpecSpace3D_PlayerController>(BasePC);
    if (PC)
    {
        PC->RequestGameOver();
    }

}