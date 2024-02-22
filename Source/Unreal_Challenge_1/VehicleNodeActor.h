// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductionBuildingActor.h"
#include "GameFramework/Actor.h"
#include "VehicleNodeActor.generated.h"

UCLASS()
class UNREAL_CHALLENGE_1_API AVehicleNodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleNodeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<AVehicleNodeActor*> adjacentNodes;
};
