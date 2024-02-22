// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductionBuildingActor.h"
#include "VehicleActor.h"
#include "GameFramework/Actor.h"
#include "ProductionManager.generated.h"

class UProductionUserWidget;

UCLASS()
class UNREAL_CHALLENGE_1_API AProductionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	UProductionUserWidget* GameWidget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateResourceList();
	//void UpdateRequestMap();

	TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> GetBuildingMap();
	UFUNCTION(BlueprintCallable)
	AProductionBuildingActor* GetBuildingFromMap(TEnumAsByte<EItemType> buildingType);
	TArray<AProductionBuildingActor*> GetBuildingArray();
	UFUNCTION(BlueprintCallable)
	TArray<AVehicleActor*> GetVehicles();
	TMap<TEnumAsByte<EItemType>, bool> GetAvailableResources();
	TArray<AProductionBuildingActor*> GetRequestQueue();
	TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> GetRequestMap();

private:
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> buildingMap;
	UPROPERTY(VisibleAnywhere)
	TArray<AProductionBuildingActor*> buildingArray;
	UPROPERTY(VisibleAnywhere)
	TArray<AVehicleNodeActor*> destinationNodes;
	UPROPERTY(VisibleAnywhere)
	TArray<AVehicleActor*> vehicles;
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, bool> availableResources;
	UPROPERTY(VisibleAnywhere)
	TArray<AProductionBuildingActor*> requestQueue;
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, AProductionBuildingActor*> requestMap;
};
