// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpecSpace3D_GameMode.generated.h"

/**
 * 
 */

// ゲーム状態配列の定義
UENUM(BlueprintType)
enum class EGameState : uint8
{
    Playing     UMETA(DisplayName = "Playing"),
    Cleared     UMETA(DisplayName = "Cleared"),
    GameOver    UMETA(DisplayName = "GameOver"),
    Menu        UMETA(DisplayName = "Menu"),
    CountDown   UMETA(DisplayName = "CountDown"),
    Paused      UMETA(DisplayName = "Paused")
};

UCLASS()
class SPEC_SPACE_3D_API ASpecSpace3D_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public : ASpecSpace3D_GameMode();

public :
       // ゲーム状態　初期は常にPlaying
       UPROPERTY(BlueprintReadOnly, Category = "State")
       EGameState CurrentState = EGameState::Playing;
       

//処理一覧
protected :
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

    FTimerHandle CountdownTimerHandle;
    int CountdownTime = 3;

    void CountdownTick();

    FTimerHandle CountdownAnimDelayHandle;


public :
    // 入力制御用のヘルパー
    bool SetInputUI();

    bool SetInputGame();

public :
    // ゲーム内処理
    UFUNCTION(BlueprintCallable, Category = "Game")
    virtual void HandleStageClear();

    UFUNCTION(BlueprintCallable, Category = "Game")
    virtual void HandleGameOver();

public:
    
    // ステージの制限時間、初期30sec
    UPROPERTY(BlueprintReadWrite, Category = "Game")
    float TimeLimit = 30.0f;

    float RemainingTime;
    float ElapsedTime;
    float ClearTime;
    int32 LastSentTime;


};