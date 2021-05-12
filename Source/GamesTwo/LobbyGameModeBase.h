// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESTWO_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintPure)
		int GetTheMaxPlayers();
	UFUNCTION(BlueprintPure)
		int GetTheNumPlayers();
private:
	UPROPERTY(EditAnywhere)
		int NumPlayers = 0;
	UPROPERTY(EditAnywhere)
		int MaxPlayers = 4;
};
