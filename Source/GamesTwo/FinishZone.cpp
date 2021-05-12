// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishZone.h"
#include "PlayableCharacter.h"
#include "Kismet\GameplayStatics.h"
// Sets default values
AFinishZone::AFinishZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	BoxComponent->SetBoxExtent({ 60.0f, 700.0f, 300.0f });
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFinishZone::BeginPlay()
{
	Super::BeginPlay();
	//Create dynamic delegate for overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishZone::OnOverlapBegin);
}

// Called every frame
void AFinishZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFinishZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		APlayableCharacter* OtherCharacter = Cast<APlayableCharacter>(OtherActor);
		if (OtherCharacter)//If other actor is a playable character
		{
			if (OtherCharacter->HasFinished == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Finished"));
				OtherCharacter->HasFinished = true;
				PlayersCrossed++;
			}
		}
	}
	if (PlayersCrossed == MaxPlayersCrossed)
	{
		GetWorld()->ServerTravel("/Game/TestLevel?listen");
	}
}