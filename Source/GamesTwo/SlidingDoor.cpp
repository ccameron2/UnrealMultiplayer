// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spinning Arm"));
	StaticMesh->SetupAttachment(RootComponent);
	
	//bReplicates = true;
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called every frame
void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation;
	if (GetActorLocation().Z >= OriginalLocation.Z)
	{
		GoingUp = false;
	}
	else if(GetActorLocation().Z <= OriginalLocation.Z - MovementAmount)
	{
		GoingUp = true;
	}
	if (GoingUp)
	{
		NewLocation = FMath::VInterpConstantTo(GetActorLocation(), OriginalLocation, DeltaTime, MovementRate);
	}
	else
	{
		NewLocation = FMath::VInterpConstantTo(GetActorLocation(), OriginalLocation + FVector(0, 0, -MovementAmount), DeltaTime, MovementRate);
	}
	SetActorLocation(NewLocation);
	FMath::RandRange(1, 4);
}

void ASlidingDoor::OnRep_MovementRate()
{
	UE_LOG(LogTemp, Warning, TEXT("Movement Rate"));
}

void ASlidingDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASlidingDoor, MovementRate);
}

