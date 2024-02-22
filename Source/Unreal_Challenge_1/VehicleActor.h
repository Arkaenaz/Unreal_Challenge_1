// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleNodeActor.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "VehicleActor.generated.h"

class AProductionManager;

UCLASS()
class UNREAL_CHALLENGE_1_API AVehicleActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RandomizeLocation();
	void CheckResources();
	void FindShortestPath();
	void FindClosestNode();
	void Start();

	TArray<TEnumAsByte<EItemType>> GetCargoLoad();
	bool IsIdle();
	void SetPickupLocation(AProductionBuildingActor* newLocation);
	void SetDropoffLocation(AProductionBuildingActor* newLocation);

	UPROPERTY(BlueprintReadWrite)
	float loadingTicks = 0.0f;
	UPROPERTY(BlueprintReadWrite)
	float loadingTime = 3.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EItemType>> cargoLoad;

private:
	UPROPERTY(EditAnywhere)
	AProductionManager* ProductionManager;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "2", ClampMax = "4", UIMin = "2", UIMax = "4"))
	int32 maxCargoLoad = 4;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "4.0", ClampMax = "8.0", UIMin = "4.0", UIMax = "8.0"))
	float travelTime = 4.0f;

	float travelTicks = 0.0f;
	
	UPROPERTY(VisibleAnywhere)
	bool loading = false;
	UPROPERTY(VisibleAnywhere)
	bool idle = false;
	UPROPERTY(VisibleAnywhere)
	bool pickUp = false;
	UPROPERTY(VisibleAnywhere)
	bool dropOff = false;
	UPROPERTY(EditAnywhere)
	AProductionBuildingActor* currentDestinationActor = nullptr;
	UPROPERTY(VisibleAnywhere)
	AProductionBuildingActor* pickUpLocation = nullptr;
	UPROPERTY(VisibleAnywhere)
	AProductionBuildingActor* dropOffLocation = nullptr;

	FVector startLocation;
	FVector targetLocation;

	void Pickup();
	void DropOff();
	void MoveVehicle();
};