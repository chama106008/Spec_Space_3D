// Fill out your copyright notice in the Description page of Project Settings.


#include "StageObject/BumperBall.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABumperBall::ABumperBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABumperBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABumperBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABumperBall::BounceActor(AActor* OtherActor)
{
	if (!OtherActor) return;

	// ÕŒ‚•ûŒüŒvŽZ
	const FVector MyLocation = GetActorLocation();
	const FVector OtherLocation = OtherActor->GetActorLocation();

	FVector Dir = (OtherLocation - MyLocation).GetSafeNormal();
	Dir.Z += 0.5f;
	Dir.Normalize();


    // Character ‚È‚ç CharacterMovement ‚É‘Î‚µ‚Ä
    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        if (UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement())
        {
            MoveComp->AddImpulse(Dir * Impulse, false);
            return;
        }
    }

    // ˆê”ÊActor‚È‚ç PrimitiveComponent ‚É‘Î‚µ‚Ä
    if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent()))
    {
        if (Prim->IsSimulatingPhysics())
        {
            // •”ˆÊŽw’è–³‚µ‚Å‘S‘Ì‚É•t—^
            Prim->AddImpulse(Dir * Impulse, NAME_None, false);
            return;
        }
    }

}

