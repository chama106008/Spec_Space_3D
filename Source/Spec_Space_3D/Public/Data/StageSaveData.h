#pragma once

#include "CoreMinimal.h"
#include "StageSaveData.generated.h"

USTRUCT(BlueprintType)
struct FStageSaveData
{
	GENERATED_BODY()

public:
    // ワールド番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WorldIndex = 0;

    // ステージ番号
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StageIndex = 0;

    // クリア状況
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCleared = false;

    // 解放状況
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocked = true;

    // ベストタイム
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BestTime = 999.0f;

};
