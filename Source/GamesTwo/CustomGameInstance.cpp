// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
UCustomGameInstance::UCustomGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Constructor"));
}


void UCustomGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Init"));
}

void UCustomGameInstance::ConsoleTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Console Test Called"));
}

void UCustomGameInstance::ConsoleTestParams(const FString Input)
{
	UE_LOG(LogTemp, Warning, TEXT("Console Test Params Called With: %s"), *Input);
}

void UCustomGameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("Called host"));

	UWorld* WorldRef = GetWorld();
	if (WorldRef != nullptr)
	{
		WorldRef->ServerTravel("/Game/Lobby?listen");
	}

}

void UCustomGameInstance::Join(const FString Input)
{
	UE_LOG(LogTemp, Warning, TEXT("Join attempted to: %s"), *Input);

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel(Input, ETravelType::TRAVEL_Absolute);
	}
}

void UCustomGameInstance::Warp(const FString LevelName)
{
	UWorld* WorldRef = GetWorld();
	if (WorldRef != nullptr)
	{
		FString Destination = FString::Printf(TEXT("/Game/%s?listen"), *LevelName);
		WorldRef->ServerTravel(Destination);
	}
}