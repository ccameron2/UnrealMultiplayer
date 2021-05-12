// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMESTWO_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UCustomGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Exec)
		virtual void Init();

	UFUNCTION(Exec)
		void ConsoleTest();

	UFUNCTION(Exec)
		void ConsoleTestParams(const FString Input);

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString Input);

	UFUNCTION(Exec)
		void Warp(const FString LevelName);
};
