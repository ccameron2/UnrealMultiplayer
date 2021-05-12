// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm and attach to staticMesh
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	// Springarm settings
	SpringArm->TargetArmLength = SpringArmLength;
	SpringArm->bEnableCameraLag = false;
	SpringArm->SetRelativeRotation((new FRotator(0.0f, 0.0f, 0.0f))->Quaternion());
	SpringArm->SetRelativeLocation(FVector(-361.0f, -305.0f, 113.0f));
	SpringArm->SetupAttachment(RootComponent);

	//Create Camera and attach to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Create Raycasting cast point for enemy characters
	RaycastingCastPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RaycastingPoint"));
	RaycastingCastPoint->SetRelativeLocation(FVector(25.0f, 0.0f, 50.0f));
	RaycastingCastPoint->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Fix issues with unreal collisions with stationary actor
	FHitResult OutHit;
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);

	FVector Location = GetActorLocation();
	if (Location.Z < -100)
	{
		if (CheckpointRef != nullptr)
		{
			SetActorLocation(FVector(CheckpointRef->GetActorLocation()), false, nullptr, ETeleportType::ResetPhysics);
		}
		else
		{
			SetActorLocation({ -200,600,0 }, false, nullptr, ETeleportType::ResetPhysics);
		}
	}
	
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayableCharacter::SetLatestCheckpoint(ACheckpoint* Checkpoint)
{
	CheckpointRef = Checkpoint;
}

void APlayableCharacter::Push()
{
	ServerPush();
}

void APlayableCharacter::ServerPush_Implementation()
{

	FCollisionQueryParams CollisionParams;

	//Create raycasting hit variables
	FHitResult Hit;
	bool bDidHit;

	//Get location of raycasting end point
	FVector End = RaycastingCastPoint->GetComponentLocation() + RaycastingCastPoint->GetComponentRotation().Vector() * CastRange;

	//Raycast from point of view
	bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, RaycastingCastPoint->GetComponentLocation(), End, ECC_Visibility, CollisionParams);

	//Trace line on screen for debugging
	//DrawDebugLine(GetWorld(), RaycastingCastPoint->GetComponentLocation(), End, FColor::Green, false, 1, 0, 1);

	if (bDidHit)//if raycast hits something
	{
		if (Hit.GetActor() != nullptr)
		{
			//Output name of hit actor to log
			UE_LOG(LogTemp, Warning, TEXT("Hit Something: %s"), *Hit.GetActor()->GetName());

			//Get root component of hit actor
			UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());

			if (Cast<APlayableCharacter>(Hit.GetActor()))//If hit a character
			{
				if (Hit.GetActor()->GetInstigatorController() == this->GetInstigatorController())
				{
					return;
				}
				//Launch other character
				Cast<APlayableCharacter>(Hit.GetActor())->LaunchCharacter(GetActorForwardVector() * DiveStrength, false, false);
			}

		}
		else
		{
			//Output successful hit to log
			UE_LOG(LogTemp, Warning, TEXT("Hit Something"));
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missed"));
	}
}

void APlayableCharacter::MoveForward(float AxisValue)
{
	//Move character forwards
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayableCharacter::Strafe(float AxisValue)
{
	//Strafe character left and right
	AddMovementInput(GetActorRightVector() * AxisValue);	
}

void APlayableCharacter::Turn(float AxisValue)
{	
	//Turn character left and right
	AddControllerYawInput(AxisValue);
	
}

void APlayableCharacter::LookUp(float AxisValue)
{

	//Rotate view up and down
	AddControllerPitchInput(AxisValue);

}

void APlayableCharacter::Dive()
{
	ServerDive();	
}

void APlayableCharacter::ServerDive_Implementation()
{
	LaunchCharacter(GetActorForwardVector() * DiveStrength, false, false);
}

bool APlayableCharacter::ServerDive_Validate()
{
	return true;
}


