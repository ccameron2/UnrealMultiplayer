// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayableCharacter.h"
#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

	UPROPERTY()
		class APlayableCharacter* MyPawn;

protected:
	void BeginPlay();

private:
	virtual void CallForward(float AxisValue);
	virtual void CallTurn(float AxisValue);
	virtual void CallStrafe(float Value);
	virtual void CallJump();
	virtual void CallLookUp(float Value);
	virtual void CallDive();

	UPROPERTY(EditAnywhere)
		float WaitTime = 12.0f;

	FTimerHandle GameStartTimerHandle;

	UFUNCTION()
		void GameStartTimerEnd();

public:
	UPROPERTY(EditAnywhere)
		bool GameStart = false;

};
