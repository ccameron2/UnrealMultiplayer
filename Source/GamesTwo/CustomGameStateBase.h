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
	void CountPlayers();
	void LogFinish();
	UFUNCTION(BlueprintPure)
		int GetFinished();
	UFUNCTION(BlueprintPure)
		int GetConnected();
	UFUNCTION(BlueprintPure)
		int GetMax();
	UPROPERTY(VisibleAnywhere, Replicated)
		bool GameStart = false;
private:
	UFUNCTION()
		void OnRep_TotalFinished();

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_TotalFinished)
		int TotalFinished = 0;
	UPROPERTY(EditAnywhere, Replicated)
		int TotalConnected = 0;
	UPROPERTY(EditAnywhere)
		int MaxPlayers = 4;

};
