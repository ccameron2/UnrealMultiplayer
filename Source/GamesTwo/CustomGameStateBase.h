// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESTWO_API ACustomGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void CountPlayers(); //Count connected players
	UFUNCTION()
		void LogFinish(); //Log finished players

	//UI Blueprint functions
	UFUNCTION(BlueprintPure)
		int GetFinished();
	UFUNCTION(BlueprintPure)
		int GetConnected();
	UFUNCTION(BlueprintPure)
		int GetMax();

	UPROPERTY(VisibleAnywhere, Replicated)//Whether or not to allow player movement
		bool GameStart = false;
private:

	UFUNCTION()
		void OnRep_TotalFinished();

	//Variables to keep track of players
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_TotalFinished)
		int TotalFinished = 0;

	UPROPERTY(EditAnywhere, Replicated)
		int TotalConnected = 0;

	UPROPERTY(EditAnywhere)
		int MaxPlayers = 4;
};
