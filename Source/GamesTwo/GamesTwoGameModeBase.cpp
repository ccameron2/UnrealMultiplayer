// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesTwoGameModeBase.h"
#include "CustomGameStateBase.h"

AGamesTwoGameModeBase::AGamesTwoGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGamesTwoGameModeBase::BeginPlay()
{
	
}

void AGamesTwoGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACustomGameStateBase* GState = GetGameState<ACustomGameStateBase>();
	GState->CountPlayers();
}

void AGamesTwoGameModeBase::LogPlayerFinished()
{
	if (ACustomGameStateBase* GState = GetGameState<ACustomGameStateBase>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Finish Logged (GameMode)"));
		GState->LogFinish();
	}
}
