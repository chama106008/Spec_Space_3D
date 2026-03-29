// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecSpace3D_GameInstance.h"
#include "Data/StageData.h"
#include "Data/StageSaveData.h"
#include "Kismet/GameplayStatics.h"

// 初期化
void USpecSpace3D_GameInstance::Init()
{
    Super::Init();

    InitializeSaveData();
    SyncSaveDataFromStages();
}

// セーブデータ取得
void USpecSpace3D_GameInstance::InitializeSaveData()
{   
    // 所定のスロットのデータ有無を確認して呼び出し
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        CurrentSaveData = Cast<USpecSpaceSaveGame>(
            UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex)
        );
    }

    // ロード失敗 or データが無ければSaveGameオブジェクトを新規作成
    if (!CurrentSaveData)
    {
        CurrentSaveData = Cast<USpecSpaceSaveGame>(
            UGameplayStatics::CreateSaveGameObject(USpecSpaceSaveGame::StaticClass())
        );

        SaveCurrentData();
    }
}

// セーブデータ保存
void USpecSpace3D_GameInstance::SaveCurrentData()
{
    if (!CurrentSaveData)
    {
        return;
    }

    UGameplayStatics::SaveGameToSlot(CurrentSaveData, SaveSlotName, UserIndex);
}

void USpecSpace3D_GameInstance::SyncSaveDataFromStages()
{
    if (!CurrentSaveData)
    {
        return;
    }

    for (FStageData& Stage : AllStages)
    {
        bool bFound = false;

        for (FStageSaveData& SaveData : CurrentSaveData->StageSaveDataArray)
        {
            if (SaveData.WorldIndex == Stage.WorldIndex &&
                SaveData.StageIndex == Stage.StageIndex)
            {
                // Save → Stage に反映
                // 解放状況は一端別管理
                // Stage.bUnlocked = SaveData.bUnlocked;
                Stage.bCleared = SaveData.bCleared;
                Stage.BestTime = SaveData.BestTime;

                bFound = true;
                break;
            }
        }

        // 無かった場合 → SaveDataを新規作成
        if (!bFound)
        {
            FStageSaveData NewData;
            NewData.WorldIndex = Stage.WorldIndex;
            NewData.StageIndex = Stage.StageIndex;
            NewData.bUnlocked = Stage.bUnlocked;
            NewData.bCleared = Stage.bCleared;
            NewData.BestTime = Stage.BestTime;

            CurrentSaveData->StageSaveDataArray.Add(NewData);
        }
    }

    // 初回補完が発生した可能性があるので保存
    SaveCurrentData();
}

void USpecSpace3D_GameInstance::ResetSaveData()
{
    if (!CurrentSaveData)
    {
        return;
    }
    
    // セーブデータをクリア
    CurrentSaveData->StageSaveDataArray.Empty();

    // StageDataを初期状態に戻す
    for (FStageData& Stage : AllStages)
    {
        Stage.bCleared = false;
        Stage.BestTime = 999.0f;
    }

    // SaveDataを再構築
    SyncSaveDataFromStages();

    // 保存
    SaveCurrentData();
}


// 現在データからStageSaveDataを更新
void USpecSpace3D_GameInstance::BuildSaveDataFromStages()
{
    if (!CurrentSaveData)
    {
        return;
    }

    CurrentSaveData->StageSaveDataArray.Empty();

    for (const FStageData& Stage : AllStages)
    {
        FStageSaveData Data;
        Data.WorldIndex = Stage.WorldIndex;
        Data.StageIndex = Stage.StageIndex;
        Data.bCleared = Stage.bCleared;
        Data.bUnlocked = Stage.bUnlocked;
        Data.BestTime = Stage.BestTime;

        CurrentSaveData->StageSaveDataArray.Add(Data);
    }
}