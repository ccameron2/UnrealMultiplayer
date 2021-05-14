// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomGameStateBase.h"
#include "PlayableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void ACustomGameStateBase::CountPlayers()
{
	if (HasAuthority())
	{
		//Get amount of actors of PlayableCharacter class in level
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), FoundActors);
		TotalConnected = FoundActors.Num();
	}
}

void ACustomGameStateBase::LogFinish()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Finish Logged (GameState)"));
		TotalFinished++;
		UE_LOG(LogTemp, Warning, TEXT("Players Finished: %i"),TotalFinished);
	}
}

int ACustomGameStateBase::GetFinished()
{
	return TotalFinished;
}

int ACustomGameStateBase::GetConnected()
{
	return TotalConnected;
}

int ACustomGameStateBase::GetMax()
{
	return MaxPlayers;
}

void ACustomGameStateBase::OnRep_TotalFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Total Finishes Replicated on Client: %i"),TotalFinished);
}

void ACustomGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACustomGameStateBase, TotalFinished);
	DOREPLIFETIME(ACustomGameStateBase, TotalConnected);
	DOREPLIFETIME(ACustomGameStateBase, GameStart);
}
