// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create skeletal mesh
	characterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));

	//Set skeletal mesh as root component
	SetRootComponent(characterMesh);

	// Create spring arm and attach to staticMesh
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	// Springarm settings
	springArm->TargetArmLength = 300.0f;
	springArm->bEnableCameraLag = false;
	springArm->SetRelativeRotation((new FRotator(0.0f, 0.0f, 0.0f))->Quaternion());
	springArm->SetRelativeLocation(FVector(-361.0f, -305.0f, 113.0f));
	springArm->SetupAttachment(characterMesh);

	//Create Camera and attach to SpringArm
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
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
}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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