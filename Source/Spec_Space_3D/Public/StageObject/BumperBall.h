// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BumperBall.generated.h"

UCLASS()
class SPEC_SPACE_3D_API ABumperBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABumperBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// è’ìÀéûÇÃèàóù
	UFUNCTION(BlueprintCallable, Category = "Hit")
	void BounceActor(AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
	float Impulse = 10000.0f;
};
