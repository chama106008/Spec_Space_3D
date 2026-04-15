// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EProcessTypes : uint8
{	
	None	UMETA(DisplayName = "None"),
	Test	UMETA(DisplayName = "Test"),
	Gravity	UMETA(DisplayName = "Gravity"),
};