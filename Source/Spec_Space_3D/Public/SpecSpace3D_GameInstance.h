#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/StageData.h"
#include "SpecSpace3D_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPEC_SPACE_3D_API USpecSpace3D_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// 全ステージ配列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage Select")
	TArray<FStageData> AllStages;

};