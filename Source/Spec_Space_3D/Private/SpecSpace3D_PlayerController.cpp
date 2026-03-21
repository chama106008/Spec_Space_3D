// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecSpace3D_PlayerController.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Character/SpecSpaceCharacter.h"

ASpecSpace3D_PlayerController::ASpecSpace3D_PlayerController()
{

}

void ASpecSpace3D_PlayerController::BeginPlay() {
	
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
	if (ACharacter* ControlCharacter = Cast<ACharacter>(GetPawn())) 
	{ 
		//移動方向はキャラクター向きではなく絶対方向 
		ControlCharacter->AddMovementInput(FVector::ForwardVector, Axis.Y); 
		ControlCharacter->AddMovementInput(FVector::RightVector, Axis.X); 
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