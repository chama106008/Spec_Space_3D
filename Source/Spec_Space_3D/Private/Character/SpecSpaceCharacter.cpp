// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SpecSpaceCharacter.h"

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

