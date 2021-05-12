// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Checkpoint.h"
#include "GamesTwoGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "GamesTwoGameModeBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class GAMESTWO_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayableCharacter();
	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	void Dive();
	void Push();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float DiveStrength = 1000.0f;

	UFUNCTION()
		void SetLatestCheckpoint(ACheckpoint* Checkpoint);

	UPROPERTY(VisibleAnywhere)
		ACheckpoint* CheckpointRef;

	UFUNCTION(Server, Reliable) //RPC
		void ServerPush();

	UPROPERTY(VisibleAnywhere)
		bool HasFinished = false;

	UFUNCTION()
		void Finished();

private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		USceneComponent* RaycastingCastPoint;

	UPROPERTY(EditAnywhere)
		float SpringArmLength = 300.0f;

	UFUNCTION(Server, Reliable, WithValidation) //RPC
		void ServerDive();

	UPROPERTY(EditAnywhere)
		float CastRange = 75.0f; //Equals 100cm when combined with raycasting point offset from player center.

	
};
