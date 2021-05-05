// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* characterMesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
};
