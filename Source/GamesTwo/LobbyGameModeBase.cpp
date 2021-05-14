// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "CustomGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"
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