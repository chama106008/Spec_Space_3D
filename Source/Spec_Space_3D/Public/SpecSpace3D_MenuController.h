// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpecSpace3D_PlayerController.h"
#include "SpecSpace3D_MenuController.generated.h"

/**
 * 
 */
UCLASS()
class SPEC_SPACE_3D_API ASpecSpace3D_MenuController : public ASpecSpace3D_PlayerController
{
	GENERATED_BODY()
	
public: ASpecSpace3D_MenuController();

protected:
	//ƒNƒ‰ƒXì¬‚Ìˆ—
	virtual void BeginPlay() override;

};
