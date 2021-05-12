// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesTwoGameModeBase.h"
#include "CustomGameStateBase.h"

void AGamesTwoGameModeBase::BeginPlay()
{
}

void AGamesTwoGameModeBase::LogPlayerFinished()
{
	if (ACustomGameStateBase* GState = GetGameState<ACustomGameStateBase>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Finish Logged (GameMode)"));
		GState->LogFinish();
	}
}
