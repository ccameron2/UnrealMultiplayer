// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameStateBase.h"

void ACustomGameStateBase::LogFinish()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Join Logged (GameState)"));
	TotalFinished++;
}