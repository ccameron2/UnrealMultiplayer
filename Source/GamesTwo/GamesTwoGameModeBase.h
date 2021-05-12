// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GamesTwoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMESTWO_API AGamesTwoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGamesTwoGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void LogPlayerFinished();

};
