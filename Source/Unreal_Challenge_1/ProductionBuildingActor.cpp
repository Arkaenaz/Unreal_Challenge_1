// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductionBuildingActor.h"

#include "ProductionManager.h"

/*#include "ItemCoal.h"
#include "ItemIron.h"
#include "ItemLumber.h"
#include "ItemSewingMachine.h"
#include "ItemSteelBeam.h"*/

// Sets default values
AProductionBuildingActor::AProductionBuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->isProducing = false;
}

// Called when the game starts or when spawned
void AProductionBuildingActor::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < this->prerequisiteItems.Num(); i++)
	{
		this->inputItemStore.Add(this->prerequisiteItems[i], 0);
	}
	this->outputItemStore.Add(this->outputItem, 0);
}

// Called every frame
void AProductionBuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = 0; i < this->prerequisiteItems.Num(); i++)
	{
		this->requestedInput.Add(this->prerequisiteItems[i], !HasPrerequisiteItem(i));
		
	}
	
	if (this->isProducing)
	{
		if (!HasPrerequisiteItems() || (outputItemStore[this->outputItem] >= this->maxOutputStorage && !unlimitedOutputStorage))
			StopProduction();
		this->Produce(DeltaTime);
	}
	else
	{
		if (HasPrerequisiteItems() && (outputItemStore[this->outputItem] < this->maxOutputStorage || unlimitedOutputStorage))
			this->StartProduction();
	}
}

void AProductionBuildingActor::PlaceItemToInput(EItemType itemType)
{
	UE_LOG(LogTemp, Display, TEXT("PLACIBG ITEMS"));
	if (this->inputItemStore[itemType] < this->maxInputStorage)
	{
		this->inputItemStore[itemType]++;
	}
}

void AProductionBuildingActor::RemoveItemFromOutput()
{
	this->outputItemStore[this->outputItem]--;
}

TEnumAsByte<EItemType> AProductionBuildingActor::GetOutputItem()
{
	return this->outputItem;
}

TMap<TEnumAsByte<EItemType>, int32> AProductionBuildingActor::GetInputStorage()
{
	return this->inputItemStore;
}

int32 AProductionBuildingActor::GetOutputStorage()
{
	return this->outputItemStore[this->outputItem];
}

TMap<TEnumAsByte<EItemType>, bool> AProductionBuildingActor::GetRequestedInput()
{
	return this->requestedInput;
}

TArray<TEnumAsByte<EItemType>> AProductionBuildingActor::GetPrerequisiteItems()
{
	return this->prerequisiteItems;
}

void AProductionBuildingActor::Produce(float DeltaTime)
{
	produceTicks += DeltaTime;
	if (produceTicks >= productionTime)
	{
		produceTicks = 0.0f;
		for (int i = 0; i < this->prerequisiteItems.Num(); i++)
		{
			if (inputItemStore[this->prerequisiteItems[i]] <= 0)
			{
				return;
			}
			inputItemStore[this->prerequisiteItems[i]]--;
		}
		outputItemStore[this->outputItem]++;
	}
}

bool AProductionBuildingActor::HasPrerequisiteItems()
{
	for (int i = 0; i < this->prerequisiteItems.Num(); i++)
	{
		if (inputItemStore[this->prerequisiteItems[i]] <= 0)
		{
			return false;
		}
	}
	return true;
}

bool AProductionBuildingActor::HasPrerequisiteItem(int index)
{
	if (inputItemStore[this->prerequisiteItems[index]] <= 0)
	{
		//UE_LOG(LogTemp, Display, TEXT("HAS NO PREREQUISITE ITEM : %d, %d, %d"), (int32)this->outputItem, index, this->inputItemStore[this->prerequisiteItems[index]]);
		return false;
	}
	return true;
}

void AProductionBuildingActor::StartProduction()
{
	this->produceTicks = 0.0f;
	this->isProducing = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s : Start Production"), *this->key.ToString()));
}

void AProductionBuildingActor::StopProduction()
{
	this->produceTicks = 0.0f;
	this->isProducing = false;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s : Stop Production"), *this->key.ToString()));
}

bool AProductionBuildingActor::IsAvailable()
{
	if (outputItemStore[this->outputItem] > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s : Available"), *this->key.ToString()));
		return true;
	}
	return false;
}

AVehicleNodeActor* AProductionBuildingActor::GetDockNode()
{
	return this->dockNode;
}
