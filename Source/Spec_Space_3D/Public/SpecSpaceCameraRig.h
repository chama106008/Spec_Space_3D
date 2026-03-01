// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecSpaceCameraRig.generated.h"



/**
 * ASpecSpaceCameraRig
 *
 * 目的：
 * - プレイヤー(ターゲット)の位置を追尾するカメラ用Actor（カメラをキャラから分離）
 * - 上下移動(Z) + 奥行き移動(ステージ前方向) でカメラ角度を微調整
 * - ほとんどの調整値をBPから触れるようにして、デバッグ＆チューニングを楽にする
 *
 */

class UCameraComponent;
class USceneComponent;

UCLASS(BlueprintType, Blueprintable)
class SPEC_SPACE_3D_API ASpecSpaceCameraRig : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecSpaceCameraRig();

	// 毎フレーム更新（追尾＆角度調整）
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// ------
	// components 
	// ------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig")	//UE側のオブジェクトラベル
	TObjectPtr<USceneComponent> Root;	//UEオブジェクトのポインター

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig")
	TObjectPtr<UCameraComponent> Camera;

	
	// ------
	// Target
	// ------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Target")
	TObjectPtr<APawn> TargetPawn;

	UFUNCTION(BlueprintCallable, Category = "SpecSpace|CameraRig|Target")
	void SetTargetPawn(APawn* NewPawn);


	// -----------------------------
	// 目標トランスフォーム計算
	// -----------------------------
	
	// 俯瞰の基本角度（見下ろし向き）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Desired", meta = (ClampMin = "-89.0", ClampMax = "0.0"))
	float BasePitch = -45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Desired", meta = (ClampMin = "-180.0", ClampMax = "180.0"))
	float BaseYaw = 45.0f;

	// Pawnから見て「どれくらい離すか」（平面距離）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Desired", meta = (ClampMin = "0.0"))
	float Distance = 900.0f;

	// Pawnから見て「どれくらい上げるか」
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Desired")
	float Height = 450.0f;

	// 必要なら左右にもずらせる（デバッグで便利）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Desired")
	float SideOffset = 0.0f;

	// ワールド座標のクランプ（巨大ステージで暴走防止。不要なら広く）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Limits")
	FVector WorldMin = FVector(-100000.0f, -100000.0f, -100000.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Limits")
	FVector WorldMax = FVector(100000.0f, 100000.0f, 100000.0f);


	// -----------------------------
	// Motion（移動方式：速度上限＋任意で加速度）
	// -----------------------------

	// 位置：最大速度（cm/s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Motion", meta = (ClampMin = "0.0"))
	float MaxSpeed = 2500.0f;

	// 位置：最大加速度（cm/s^2）。加速度を使わないなら0でOK
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Motion", meta = (ClampMin = "0.0"))
	float MaxAccel = 0.0f;

	// 回転：最大角速度（deg/s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpecSpace|CameraRig|Motion", meta = (ClampMin = "0.0"))
	float MaxTurnRateDeg = 240.0f;

private:
	// 加速度方式のときに使う現在速度
	FVector CurrentVelocity = FVector::ZeroVector;

private:
	bool EnsureTargetPawn();

	// Pawn位置から「目的座標」を作る
	FVector ComputeDesiredLocation(const FVector& PawnLocation) const;

	// 基本角度のみの「目的回転」（必要なら後で“上下＋奥行きで角度変更”を追加できる）
	FRotator ComputeDesiredRotation() const;

};
