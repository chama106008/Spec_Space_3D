// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/StageSaveData.h"
#include "SpecSpaceSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SPEC_SPACE_3D_API USpecSpaceSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStageSaveData> StageSaveDataArray;

};
