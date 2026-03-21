// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpecSpace3D_PlayerController.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SPEC_SPACE_3D_API ASpecSpace3D_PlayerController : public APlayerController
{
	GENERATED_BODY()

public: ASpecSpace3D_PlayerController();



protected:
	//クラス作成時の処理
	virtual void BeginPlay() override;

	//入力基盤が作製された直後の処理
	virtual void SetupInputComponent() override;

	//移動入力処理
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnMoveAxis(FVector2D Axis);

	void OnMove(const FInputActionValue& Value);

	//ジャンプ入力処理
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnJump(bool Pressed);

	// 透過モード
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnGhost(bool Pressed);

	// 軽量化モード
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnFeather(bool Pressed);

	// 滑走モード
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnSlip(bool Pressed);
};
