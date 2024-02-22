// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleActor.h"

#include "ProductionManager.h"
#include "VehicleNodeActor.h"
#include "Kismet/GameplayStatics.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AVehicleActor::AVehicleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleActor::BeginPlay()
{
	Super::BeginPlay();

	this->startLocation = this->GetActorLocation();
	this->idle = true;
	RandomizeLocation();;
	//this->pickUp = true;
}

// Called every frame
void AVehicleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (loading)
	{
		this->loadingTicks += DeltaTime;
		if (this->loadingTicks >= this->loadingTime) {
			this->loading = false;
			this->loadingTicks = 0.0f;
			if (pickUp)
				Pickup();
			else if (dropOff)
				DropOff();
			
		}
	}
	else
	{
		this->travelTicks += DeltaTime;
		if (this->pickUpLocation != nullptr)
		{
			this->currentDestinationActor = this->pickUpLocation;
			targetLocation = this->pickUpLocation->GetDockNode()->GetActorLocation();
		}
		else if (this->dropOffLocation != nullptr)
		{
			this->currentDestinationActor = this->dropOffLocation;
			targetLocation = this->dropOffLocation->GetDockNode()->GetActorLocation();
		}
		MoveVehicle();
		if (this->travelTicks >= this->travelTime)
		{
			this->startLocation = this->targetLocation;
			if (idle)
			{
				RandomizeLocation();
				CheckResources();
			}
			else
			{
				this->loading = true;
				this->loadingTime = FMath::RandRange(1, 3);
				
			}
			this->travelTicks = 0.0f;
		}
	}
	if (!pickUp && !dropOff && !loading)
	{
		this->idle = true;
		CheckResources();
	}
}

void AVehicleActor::RandomizeLocation()
{
	float x = FMath::RandRange(this->startLocation.X - 2500.0f, this->startLocation.X + 2500.0f);
	float y = FMath::RandRange(this->startLocation.Y - 2500.0f, this->startLocation.Y + 2500.0f);
	this->targetLocation = FVector(x,y, this->GetActorLocation().Z);
}

void AVehicleActor::CheckResources()
{
	for (auto requests : this->ProductionManager->GetRequestMap())
	{
		for (auto item : this->ProductionManager->GetAvailableResources())
		{
			if (item.Value && item.Key == requests.Key)
			{
				if (requests.Value->GetRequestedInput()[item.Key] && (!pickUp || !dropOff))
				{
					AProductionBuildingActor* tempBuilding = this->ProductionManager->GetBuildingMap()[item.Key];
					if (!tempBuilding->scheduled)
					{
						this->pickUpLocation = tempBuilding;
						this->dropOffLocation = requests.Value;
						this->currentDestinationActor = this->pickUpLocation;
						this->targetLocation = this->pickUpLocation->GetDockNode()->GetActorLocation();
						requests.Value->requested = false;
						this->pickUpLocation->scheduled = true;
						// this->dropOffLocation->scheduled = true;
						Start();
						break;
					}
				}
			}
		}
	}
}

TArray<TEnumAsByte<EItemType>> AVehicleActor::GetCargoLoad()
{
	return this->cargoLoad;
}

void AVehicleActor::Pickup()
{
	if (this->currentDestinationActor == nullptr)
		return;
	AProductionBuildingActor* buildingActor = this->currentDestinationActor;
	for (int i = this->cargoLoad.Num(); i < maxCargoLoad; i++)
	{
		if (buildingActor->GetOutputStorage() > 0) {
			buildingActor->RemoveItemFromOutput();
			this->cargoLoad.Add(buildingActor->GetOutputItem());
		}
	}
	pickUp = false;
	this->currentDestinationActor->scheduled = false;
	this->pickUpLocation->scheduled = false;
	this->pickUpLocation = nullptr;
	
}

void AVehicleActor::DropOff()
{
	if (this->currentDestinationActor == nullptr)
		return;
	AProductionBuildingActor* buildingActor = this->currentDestinationActor;
	
	this->targetLocation = this->currentDestinationActor->GetDockNode()->GetActorLocation();
	this->currentDestinationActor = this->dropOffLocation;
	for (int i = cargoLoad.Num() - 1; i >= 0; i--)
	{
		buildingActor->PlaceItemToInput(cargoLoad[i]);
		cargoLoad.RemoveAt(i);
	}
	dropOff = false;
	this->dropOffLocation->requested = false;
	this->currentDestinationActor->scheduled = false;
	this->dropOffLocation->scheduled = false;
	this->dropOffLocation = nullptr;
}

void AVehicleActor::MoveVehicle()
{
	this->SetActorLocation(FMath::Lerp(this->startLocation, this->targetLocation, this->travelTicks / this->travelTime));
	this->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->startLocation, this->targetLocation));
}

void AVehicleActor::Start()
{
	this->startLocation = this->GetActorLocation();
	idle = false;
	pickUp = true;
	dropOff = true;
}

void AVehicleActor::SetPickupLocation(AProductionBuildingActor* newLocation)
{
	this->pickUpLocation = newLocation;
}

void AVehicleActor::SetDropoffLocation(AProductionBuildingActor* newLocation)
{
	this->dropOffLocation = newLocation;
}

bool AVehicleActor::IsIdle()
{
	return this->idle;
}