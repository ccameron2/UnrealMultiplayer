// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishZone.h"
#include "PlayableCharacter.h"
#include "Kismet\GameplayStatics.h"


// Sets default values
AFinishZone::AFinishZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create trigger box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	BoxComponent->SetBoxExtent({ 60.0f, 700.0f, 300.0f });
	BoxComponent->SetupAttachment(RootComponent);

	//Create Niagara components and attach to root component
	Niagara1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara 1"));
	Niagara1->SetupAttachment(RootComponent);
	Niagara2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara 2"));
	Niagara2->SetupAttachment(RootComponent);
	bReplicates = true;

}

// Called when the game starts or when spawned
void AFinishZone::BeginPlay()
{
	Super::BeginPlay();
	//Create dynamic delegate for overlap events
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFinishZone::OnOverlapBegin);
	SetReplicates(true);
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
			if (OtherCharacter->HasFinished == false)//If player has not already crossed the line
			{
				if (PlayersCrossed == 0)
				{
					if (HasAuthority())
					{
						MultiNiagara();
					}			
				}
				UE_LOG(LogTemp, Warning, TEXT("Player Finished"));
				//Log player has finished on their game state
				OtherCharacter->Finished();
				//Count Player
				PlayersCrossed++;
				//Play Sound
				ClientSound();
			}
		}
	}
	if (PlayersCrossed == MaxPlayersCrossed)
	{
		//Move players to finish level
		GetWorld()->ServerTravel("/Game/Finish?listen");
	}
}

void AFinishZone::MultiNiagara_Implementation()
{
	Niagara1->Activate();
	Niagara2->Activate();
}

void AFinishZone::ClientSound_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Sound Played"));
	//Play sound on client
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WinSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
}
