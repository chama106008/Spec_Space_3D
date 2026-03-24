#pragma once

#include "CoreMinimal.h"
#include "StageData.generated.h"

USTRUCT(BlueprintType)
struct FStageData
{
    GENERATED_BODY()

public:
    // ワールド番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WorldIndex = 0;

    // ステージ番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StageIndex = 0;

    // ステージ名
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText StageTitle;

    // 呼び出しレベル名
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LevelName;

    // 時間制限
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeLimit = 30.0f;

    // ベストタイム
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BestTime = 999.0f;

    // 解放状況
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocked = true;

};
