// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecSpace3D_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "SpecSpace3D_PlayerController.h"

ASpecSpace3D_GameMode::ASpecSpace3D_GameMode()
{

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



// -------------
// 通常処理
// -------------

void ASpecSpace3D_GameMode::BeginPlay()
{
	CurrentState = EGameState::Playing;
    SetInputGame();
}

//クリア時処理
void ASpecSpace3D_GameMode::HandleStageClear()
{   
    if (CurrentState != EGameState::Playing)
    {
        return;
    }
    
    CurrentState = EGameState::Cleared;
    SetInputUI();

    //controllerからUI処理を呼び出し
    APlayerController* BasePC = UGameplayStatics::GetPlayerController(this, 0);
    ASpecSpace3D_PlayerController* PC = Cast<ASpecSpace3D_PlayerController>(BasePC);
    if (PC)
    {
        PC->RequestStageClear();
    }


}

//ゲームオーバー処理
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