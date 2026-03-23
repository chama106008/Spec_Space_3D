// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecSpaceCameraRig.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpecSpaceCameraRig::ASpecSpaceCameraRig()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//コンポーネント付与
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ASpecSpaceCameraRig::BeginPlay()
{
	Super::BeginPlay();
	
}

// 毎フレーム移動
void ASpecSpaceCameraRig::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bFreezeCamera) return;

	if (!EnsureTargetPawn())
	{
		return;
	}

	const FVector PawnLoc = TargetPawn->GetActorLocation();

	// 目的値を計算
	const FVector DesiredLoc = ComputeDesiredLocation(PawnLoc);
	const FRotator DesiredRot = ComputeDesiredRotation(PawnLoc);


	// 2) 位置：速度上限で近づく（＋任意で加速度）
	const FVector CurrentLoc = GetActorLocation();
	if (MaxAccel <= 0.0f)
	{
		// 加速度なし：最大速度で一定移動（シンプル）
		// VInterpConstantToは「速度上限で近づく」挙動になる
		const FVector NewLoc = FMath::VInterpConstantTo(CurrentLoc, DesiredLoc, DeltaSeconds, MaxSpeed);
		SetActorLocation(NewLoc);
	}
	else
	{
		// 加速度あり：目標へ向かう“理想速度”を作り、加速度上限で追従する
		const FVector ToTarget = (DesiredLoc - CurrentLoc);
		const float Dist = ToTarget.Length();

		if (Dist < KINDA_SMALL_NUMBER)
		{
			CurrentVelocity = FVector::ZeroVector;
			SetActorLocation(DesiredLoc);
		}
		else
		{
			// 理想速度：ターゲット方向へMaxSpeed
			const FVector DesiredVel = ToTarget.GetSafeNormal() * MaxSpeed;

			// 速度をDesiredVelへ寄せるが、加速度上限で変化量を制限
			const FVector VelDelta = DesiredVel - CurrentVelocity;

			const float MaxDelta = MaxAccel * DeltaSeconds;
			const FVector ClampedVelDelta =
				(VelDelta.Length() <= MaxDelta) ? VelDelta : VelDelta.GetSafeNormal() * MaxDelta;

			CurrentVelocity += ClampedVelDelta;

			// 位置更新
			FVector NewLoc = CurrentLoc + CurrentVelocity * DeltaSeconds;

			// 行き過ぎ防止：近づきすぎたら目的地にスナップ
			if ((DesiredLoc - NewLoc).Dot(DesiredLoc - CurrentLoc) <= 0.0f)
			{
				NewLoc = DesiredLoc;
				CurrentVelocity = FVector::ZeroVector;
			}

			SetActorLocation(NewLoc);
		}
	}

	// 3) 回転：角速度上限で近づく
	// RInterpConstantToは「最大deg/s」で一定回転
	const FRotator NewRot = FMath::RInterpConstantTo(GetActorRotation(), DesiredRot, DeltaSeconds, MaxTurnRateDeg);
	SetActorRotation(NewRot);
}

void ASpecSpaceCameraRig::SetCameraFreeze(bool bFreeze)
{
	bFreezeCamera = bFreeze;
}

//追跡対象を取得
void ASpecSpaceCameraRig::SetTargetPawn(APawn* NewPawn)
{
    TargetPawn = NewPawn;
    CurrentVelocity = FVector::ZeroVector;
}

bool ASpecSpaceCameraRig::EnsureTargetPawn()
{
	if (IsValid(TargetPawn))
	{
		return true;
	}

	APawn* Pawn0 = UGameplayStatics::GetPlayerPawn(this, 0);
	if (IsValid(Pawn0))
	{
		TargetPawn = Pawn0;
		CurrentVelocity = FVector::ZeroVector;
		return true;
	}

	return false;
}

//座標計算
FVector ASpecSpaceCameraRig::ComputeDesiredLocation(const FVector& PawnLocation) const
{
	//Xは前後、Yは左右、Zは高低

	FVector Desired = PawnLocation;

	//各位置設定
	const float Normalized = FMath::Abs(PawnLocation.Z - Height) / Height;
	const float Clamped = FMath::Min(Normalized, 1.0f);
	const float Factor = sqrt(Clamped * (2.0f - Clamped));   // 0→1へ滑らかに増える
	Desired.X -= Distance * (1.0f + 0.5f * Factor);
	Desired.Y += SideOffset;
	Desired.Z = Height;

	// ワールド範囲にクランプ（暴走防止）
	Desired.X = FMath::Clamp(Desired.X, WorldMin.X, WorldMax.X);
	Desired.Y = FMath::Clamp(Desired.Y, WorldMin.Y, WorldMax.Y);
	Desired.Z = FMath::Clamp(Desired.Z, WorldMin.Z, WorldMax.Z);

	return Desired;
}

//角度計算
FRotator ASpecSpaceCameraRig::ComputeDesiredRotation(const FVector& PawnLocation) const
{
	// 今は最小：固定の俯瞰角のみ
	FRotator Desired = FRotator(BasePitch, BaseYaw, 0.0f);

	Desired.Pitch = BasePitch * (1 - PawnLocation.Z / Height) + 3.0f;
	Desired.Pitch = FMath::Clamp(Desired.Pitch, -80.0f, 80.0f);

	return Desired;
}