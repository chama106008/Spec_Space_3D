#pragma once

#include "CoreMinimal.h"
#include "EColorTypes.generated.h"

UENUM(BlueprintType)
enum class EColorGroup : uint8
{
	None	UMETA(DisplayName = "None"),
	Red		UMETA(DisplayName = "Red"),
	Blue	UMETA(DisplayName = "Blue"),
	Green	UMETA(DisplayName = "Green"),
	Yellow	UMETA(DisplayName = "Yellow")
};