#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/StageData.h"
#include "Data/StageSaveData.h"
#include "SpecSpaceSaveGame.h"
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

	// セーブデータ配列
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USpecSpaceSaveGame> CurrentSaveData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SaveSlotName = TEXT("MainSlot");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 UserIndex = 0;

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void InitializeSaveData();

	UFUNCTION(BlueprintCallable)
	void SaveCurrentData();

	UFUNCTION(BlueprintCallable)
	void SyncSaveDataFromStages();

	UFUNCTION(BlueprintCallable)
	void ResetSaveData();

	UFUNCTION(BlueprintCallable)
	void BuildSaveDataFromStages();
};