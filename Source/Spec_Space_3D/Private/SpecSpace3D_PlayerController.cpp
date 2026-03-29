// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecSpace3D_PlayerController.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Character/SpecSpaceCharacter.h"
#include "SpecSpace3D_GameMode.h"
#include "Kismet/GameplayStatics.h"

ASpecSpace3D_PlayerController::ASpecSpace3D_PlayerController()
{

}

void ASpecSpace3D_PlayerController::BeginPlay() 
{
	
	Super::BeginPlay();

}

void ASpecSpace3D_PlayerController::SetupInputComponent() {
	
	Super::SetupInputComponent();

}

//------
// 移動処理
// ------
void ASpecSpace3D_PlayerController::OnMove(const FInputActionValue& Value)
{
    const FVector2D Axis = Value.Get<FVector2D>();
    OnMoveAxis(Axis);
}

void ASpecSpace3D_PlayerController::OnMoveAxis(FVector2D Axis)
{
	if (ASpecSpaceCharacter* ControlCharacter = Cast<ASpecSpaceCharacter>(GetPawn())) 
	{	
		if (IsCameraRig)
		{
			//移動方向はキャラクター向きではなく絶対方向 
			ControlCharacter->AddMovementInput(FVector::ForwardVector, Axis.Y); 
			ControlCharacter->AddMovementInput(FVector::RightVector, Axis.X);
		}
		else
		{
			const FRotator ControlRot = GetControlRotation();
			const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

			const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
			const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

			ControlCharacter->AddMovementInput(ForwardDir, Axis.Y);
			ControlCharacter->AddMovementInput(RightDir, Axis.X);
		}
		
		
		// アニメーション用の入力判定
		// 入力値そのものだけ保存
		ControlCharacter->MoveInputAxis = Axis;
	}
}


//------
// ジャンプ処理
// ------
void ASpecSpace3D_PlayerController::OnJump(bool Pressed)
{
	if (ACharacter* ControlCharacter = Cast<ACharacter>(GetPawn()))
	{
		if (Pressed)
		{	
			ControlCharacter->Jump();
		}
		else
		{
			ControlCharacter->StopJumping();
		}
	}
}

// -------
// 当たり判定消失ギミック
// -------
void ASpecSpace3D_PlayerController::OnGhost(bool Pressed)
{
	if (ASpecSpaceCharacter* ControlCharacter = Cast<ASpecSpaceCharacter>(GetPawn()))
	{
		if (Pressed)
		{
			ControlCharacter->SetGhostMode(true);
		}
		else
		{
			ControlCharacter->SetGhostMode(false);
		}
	}

}

// -------
// 軽量化ギミック
// -------
void ASpecSpace3D_PlayerController::OnFeather(bool Pressed)
{
	if (ASpecSpaceCharacter* ControlCharacter = Cast<ASpecSpaceCharacter>(GetPawn()))
		if (Pressed)
		{
			ControlCharacter->SetFeatherMode(true);
		}
		else
		{
			ControlCharacter->SetFeatherMode(false);
		}
}


// -------
// 滑走ギミック
// -------
void ASpecSpace3D_PlayerController::OnSlip(bool Pressed)
{
	if (ASpecSpaceCharacter* ControlCharacter = Cast<ASpecSpaceCharacter>(GetPawn()))
		if (Pressed)
		{
			ControlCharacter->SetSlipMode(true);
		}
		else
		{
			ControlCharacter->SetSlipMode(false);
		}
}

// -------
// ポーズ処理
// -------
void ASpecSpace3D_PlayerController::TogglePause()
{	
	ASpecSpace3D_GameMode* GM = Cast<ASpecSpace3D_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		if (GM->CurrentState == EGameState::CountDown)
			return;
	}

	if (!IsPaused)
	{
		PauseGame();
	}
	else
	{
		ResumeGame();
	}
}

void ASpecSpace3D_PlayerController::PauseGame()
{
	IsPaused = true;
	ASpecSpace3D_GameMode* GM = Cast<ASpecSpace3D_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->CurrentState = EGameState::Paused;
		GM->SetInputBoth();
	}
	else return;

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ASpecSpace3D_PlayerController::ResumeGame()
{
	IsPaused = false;
	ASpecSpace3D_GameMode* GM = Cast<ASpecSpace3D_GameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->CurrentState = EGameState::Playing;
		GM->SetInputGame();
	}
	else return;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}