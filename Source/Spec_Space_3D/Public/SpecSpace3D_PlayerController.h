// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpecSpace3D_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPEC_SPACE_3D_API ASpecSpace3D_PlayerController : public APlayerController
{
	GENERATED_BODY()

public: ASpecSpace3D_PlayerController();

protected:
	//ƒNƒ‰ƒXì¬‚Ìˆ—
	virtual void BeginPlay() override;

	//“ü—ÍŠî”Õ‚ªì»‚³‚ê‚½’¼Œã‚Ìˆ—
	virtual void SetupInputComponent() override;

};
