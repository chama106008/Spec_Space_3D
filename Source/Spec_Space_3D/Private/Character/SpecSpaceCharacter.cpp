// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SpecSpaceCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASpecSpaceCharacter::ASpecSpaceCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ASpecSpaceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpecSpaceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpecSpaceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// 透過モード(見た目の変更は保留)
void ASpecSpaceCharacter::SetGhostMode(bool bEnable)
{
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		if (bEnable)
		{
			Capsule->SetCollisionProfileName(TEXT("GhostPawn"));
		}
		else
		{
			Capsule->SetCollisionProfileName(TEXT("NormalPawn"));
		}
	}

	if (bEnable)
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			MoveComp->SetMovementMode(MOVE_Falling);
		}
	}
	
}

// 軽量モード(見た目の変更は保留)
void ASpecSpaceCharacter::SetFeatherMode(bool bEnable)
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		if (bEnable)
		{
			MoveComp->Mass = 1.0f;
		}
		else
		{
			MoveComp->Mass = 100.0f;
		}
	}
}

// 滑走モード(見た目の変更は保留)
void ASpecSpaceCharacter::SetSlipMode(bool bEnable)
{

}