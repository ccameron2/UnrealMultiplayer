// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningArm.h"
#include "Net/UnrealNetwork.h"
// Sets default values
ASpinningArm::ASpinningArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spinning Arm"));
	SetRootComponent(StaticMesh);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASpinningArm::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		NetUpdateFrequency = 5;
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

// Called every frame
void ASpinningArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (HasAuthority())
	//{
		FRotator Rotation = { 0.f, RotationRate * DeltaTime, 0.f };
		AddActorLocalRotation(Rotation);
	//}
}

void ASpinningArm::OnRep_RotationRate()
{
	UE_LOG(LogTemp, Warning, TEXT("Replicated Rotation"));
}

void ASpinningArm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASpinningArm, RotationRate);
}

