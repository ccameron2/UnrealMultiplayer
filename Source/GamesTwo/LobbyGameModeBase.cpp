// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "CustomGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"
#include "Net/UnrealNetwork.h"
#include "CustomPlayerController.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	NumPlayers++;
	if (NumPlayers == MaxPlayers)
	{

		GetWorld()->ServerTravel("Level");
	}
}

int ALobbyGameModeBase::GetTheMaxPlayers()
{
	return MaxPlayers;
}

int ALobbyGameModeBase::GetTheNumPlayers()
{
	return NumPlayers;
}
void ALobbyGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGameModeBase, NumPlayers);
	DOREPLIFETIME(ALobbyGameModeBase, MaxPlayers);
}
