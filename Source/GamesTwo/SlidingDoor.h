// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.generated.h"

UCLASS()
class GAMESTWO_API ASlidingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlidingDoor();
	bool GoingUp = false;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle WaitTimer;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_MovementRate)
		float MovementRate = 200.0f;

	UPROPERTY(EditAnywhere, Replicated)
		bool IsMoving = true;

	UFUNCTION()
		void OnRep_MovementRate();

	UPROPERTY(VisibleAnywhere)
		FVector OriginalLocation;

	UPROPERTY(EditAnywhere)
		float MovementAmount = 300.0f;

	UFUNCTION(NetMultiCast, Reliable)
		void OnWaitEnd();

	UFUNCTION()
		void StartWait();

};
