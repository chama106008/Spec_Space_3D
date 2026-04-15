// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EColorTypes.h"
#include "Data/EProcessTypes.h"
#include "Components/ActorComponent.h"
#include "ColorSwitchTargetComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))


class SPEC_SPACE_3D_API UColorSwitchTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UColorSwitchTargetComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EColorGroup ColorGroup = EColorGroup::None;

	UFUNCTION(BlueprintCallable)
	virtual void Execute(EProcessTypes Type);


protected:
	virtual void BeginPlay() override;

	// èàóùàÍóó
	virtual void Test();
	virtual void SetGravity();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



		
};
