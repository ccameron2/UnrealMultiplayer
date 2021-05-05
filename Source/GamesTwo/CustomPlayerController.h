// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayableCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMESTWO_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetupInputComponent();

	UPROPERTY(EditAnywhere)
		class APlayableCharacter* MyPawn;

protected:
	void BeginPlay();

private:
	virtual void CallForward(float AxisValue);
	virtual void CallTurn(float AxisValue);
	virtual void CallStrafe(float Value);
	virtual void CallJump();
	virtual void CallLookUp(float Value);
};
