// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionManager.h"

#include "Blueprint/UserWidget.h"
#include "ProductionUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProductionManager::AProductionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProductionManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> buildingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProductionBuildingActor::StaticClass(), buildingActors);
	for (int i = 0; i < buildingActors.Num(); i++)
	{
		buildingMap.Add(Cast<AProductionBuildingActor>(buildingActors[i])->GetOutputItem(),Cast<AProductionBuildingActor>(buildingActors[i]));
		buildingArray.Add(Cast<AProductionBuildingActor>(buildingActors[i]));
;	}

	TArray<AActor*> vehicleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleActor::StaticClass(), vehicleActors);
	for (int i = 0; i < vehicleActors.Num(); i++)
	{
		vehicles.Add(Cast<AVehicleActor>(vehicleActors[i]));
	}
	for (int i = 0; i < this->buildingArray.Num(); i++)
	{
		this->availableResources.Add(buildingArray[i]->GetOutputItem(), false);
		/*for (int j = 0; j < this->buildingArray[i]->GetPrerequisiteItems().Num(); j++)
		{
			this->requestMap.Add(this->buildingArray[i]->GetPrerequisiteItems()[j], buildingArray[i]);
		}*/
	}
	if (GameWidgetClass)
	{
		GameWidget = Cast<UProductionUserWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			UE_LOG(LogTemp, Display, TEXT("SPAWNED GAME WIDGET"));
			GameWidget->AddToViewport();
		}
	}
}

// Called every frame
void AProductionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateResourceList();
	for (int i = 0; i < this->buildingArray.Num(); i++)
	{
		for (int j = 0; j < this->buildingArray[i]->GetPrerequisiteItems().Num(); j++)
		{
			if (!this->buildingArray[i]->HasPrerequisiteItem(j) && !this->buildingArray[i]->requested)
			{
				if (!this->requestQueue.Contains(this->buildingArray[i]))
					this->requestQueue.Push(this->buildingArray[i]);
			}
			if (this->buildingArray[i]->GetRequestedInput().Contains(this->buildingArray[i]->GetPrerequisiteItems()[j]))
			{
				if (this->buildingArray[i]->GetRequestedInput()[this->buildingArray[i]->GetPrerequisiteItems()[j]])
					this->requestMap.Add(this->buildingArray[i]->GetPrerequisiteItems()[j], this->buildingArray[i]);
			}
		}
	}
	//UpdateRequestMap();
}

void AProductionManager::UpdateResourceList()
{
	for (int i = 0; i < this->buildingArray.Num(); i++)
	{
		if (buildingArray[i]->IsAvailable())
			this->availableResources[buildingArray[i]->GetOutputItem()] = true;
		else
			this->availableResources[buildingArray[i]->GetOutputItem()] = false;
	}
}

/*void AProductionManager::UpdateRequestMap()
{
	for (int i = 0; i < this->buildingArray.Num(); i++)
	{
		for (int j = 0; j < this->buildingArray[i]->GetPrerequisiteItems().Num(); j++)
		{
			if (this->buildingArray[i]->GetInputStorage()[this->buildingArray[i]->GetPrerequisiteItems()[j]] <= 0)
			{
				this->requestQueue.Add(this->buildingArray[i]->GetPrerequisiteItems()[j], this->buildingArray[i]);
			}
		}
	}
	
}*/

TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> AProductionManager::GetBuildingMap()
{
	return this->buildingMap;
}

AProductionBuildingActor* AProductionManager::GetBuildingFromMap(TEnumAsByte<EItemType> buildingType)
{
	UE_LOG(LogTemp, Display, TEXT("%s"),*this->buildingMap[buildingType]->GetActorNameOrLabel());
	return this->buildingMap[buildingType];
}

TArray<AProductionBuildingActor*> AProductionManager::GetBuildingArray()
{
	return this->buildingArray;
}

TArray<AVehicleActor*> AProductionManager::GetVehicles()
{
	return this->vehicles;
}

TMap<TEnumAsByte<EItemType>, bool> AProductionManager::GetAvailableResources()
{
	return this->availableResources;
}

TArray<AProductionBuildingActor*> AProductionManager::GetRequestQueue()
{
	return this->requestQueue;
}

TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> AProductionManager::GetRequestMap()
{
	return this->requestMap;
}

