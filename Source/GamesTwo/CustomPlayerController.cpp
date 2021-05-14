// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomPlayerController.h"
#include "CustomGameStateBase.h"


void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Get pawn reference
	MyPawn = Cast<APlayableCharacter>(GetPawn());
	if (Cast<ACustomGameStateBase>(GetWorld()->GetGameState()))
	{
		GameStart = Cast<ACustomGameStateBase>(GetWorld()->GetGameState())->GameStart;
	}
	if (GameStart == false)
	{
		GetWorld()->GetTimerManager().SetTimer(GameStartTimerHandle, this, &ACustomPlayerController::GameStartTimerEnd, WaitTime, false);
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	//Bind inputs to assigned functions
	InputComponent->BindAxis("Move Forwards", this, &ACustomPlayerController::CallForward);
	InputComponent->BindAxis("Turn", this, &ACustomPlayerController::CallTurn);
	InputComponent->BindAxis("Strafe", this, &ACustomPlayerController::CallStrafe);
	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallJump);
	InputComponent->BindAxis("Look Up", this, &ACustomPlayerController::CallLookUp);
	InputComponent->BindAction("Dive", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallDive);
	InputComponent->BindAction("Push", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallPush);
}

void ACustomPlayerController::CallForward(float Value)
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->MoveForward(Value);
		}
	}
}

void ACustomPlayerController::CallTurn(float Value)
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->Turn(Value);
		}
	}
	
}


void ACustomPlayerController::CallStrafe(float Value)
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->Strafe(Value);
		}
	}
}

void ACustomPlayerController::CallJump()
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->Jump();
		}
	}
}

void ACustomPlayerController::CallLookUp(float Value)
{
	if (GameStart)
	{
		if (MyPawn)
		{
			if (InvertMouse)
			{
				MyPawn->LookUp(Value);
			}
			else
			{
				MyPawn->LookUp(-Value);
			}
		}
	}
}

void ACustomPlayerController::CallDive()
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->Dive();
		}
	}
}

void ACustomPlayerController::CallPush()
{
	if (GameStart)
	{
		if (MyPawn)
		{
			MyPawn->Push();
		}
	}
}

void ACustomPlayerController::GameStartTimerEnd()
{
	GameStart = true;
}
