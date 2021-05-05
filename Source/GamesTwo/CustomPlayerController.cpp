// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//Get pawn reference
	MyPawn = Cast<APlayableCharacter>(GetPawn());
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

}

void ACustomPlayerController::CallForward(float Value)
{
	if (MyPawn)
	{
		MyPawn->MoveForward(Value);
	}
}

void ACustomPlayerController::CallTurn(float Value)
{
	if (MyPawn)
	{
		MyPawn->Turn(Value);
	}
}


void ACustomPlayerController::CallStrafe(float Value)
{
	if (MyPawn)
	{
		MyPawn->Strafe(Value);
	}
}

void ACustomPlayerController::CallJump()
{
	if (MyPawn)
	{
		MyPawn->Jump();
	}
}

void ACustomPlayerController::CallLookUp(float Value)
{
	if (MyPawn)
	{
		MyPawn->LookUp(Value);
	}
}