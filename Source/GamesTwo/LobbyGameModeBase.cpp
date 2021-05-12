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
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), FoundActors);
		for (int i = 0; i < FoundActors.Num(); i++)
		{
			Cast<ACustomPlayerController>(Cast<APlayableCharacter>(FoundActors[i])->GetInstigatorController())->GameStart = false;
		}
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
