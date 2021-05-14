// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
//#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinishZone.generated.h"


UCLASS()
class GAMESTWO_API AFinishZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere)
		int PlayersCrossed = 0;
	UPROPERTY(EditAnywhere)
		int MaxPlayersCrossed = 4;
	UFUNCTION(Client, Reliable) //RPC
		void ClientSound();
	UFUNCTION(NetMulticast, Reliable) //RPC
		void MultiNiagara();
	UPROPERTY(EditAnywhere)
		USoundBase* WinSound;
	//UPROPERTY(EditAnywhere)
	//	UNiagraComponent* Niagra1;
	//UPROPERTY(EditAnywhere)
	//	UNiagraComponent* Niagra2;

};
