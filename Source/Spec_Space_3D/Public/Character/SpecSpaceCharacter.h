// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpecSpaceCharacter.generated.h"

UCLASS()
class SPEC_SPACE_3D_API ASpecSpaceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpecSpaceCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ---------
	// 新規アクションギミック
	// ---------
	// 透過モード
	UFUNCTION()
	virtual void SetGhostMode(bool bEnable);
};
