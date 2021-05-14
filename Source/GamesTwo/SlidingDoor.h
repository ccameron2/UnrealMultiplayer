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
	bool Moving = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_MovementRate)
		float MovementRate = 200.0f;

	UFUNCTION()
		void OnRep_MovementRate();

	UPROPERTY(VisibleAnywhere)
		FVector OriginalLocation;

	UPROPERTY(EditAnywhere)
		float MovementAmount = 200.0f;

};
