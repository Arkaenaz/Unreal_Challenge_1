// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ItemClass.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "ProductionBuildingActor.generated.h"

class AProductionManager;
class AVehicleNodeActor;

UENUM(BlueprintType)
enum EItemType
{
	None UMETA(DisplayName = "None"),
	Iron UMETA(DisplayName = "Iron"),
	Coal UMETA(DisplayName = "Coal"),
	SteelBeams UMETA(DisplayName = "Steel Beams"),
	Lumber UMETA(DisplayName = "Lumber"),
	SewingMachine UMETA(DisplayName = "Sewing Machine")
};

UCLASS()
class UNREAL_CHALLENGE_1_API AProductionBuildingActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProductionBuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void StartProduction();
	virtual void StopProduction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlaceItemToInput(EItemType itemType);
	void RemoveItemFromOutput();

	TEnumAsByte<EItemType> GetOutputItem();
	UFUNCTION(BlueprintCallable)
	TMap<TEnumAsByte<EItemType>, int32> GetInputStorage();
	UFUNCTION(BlueprintCallable)
	int32 GetOutputStorage();
	TMap<TEnumAsByte<EItemType>, bool> GetRequestedInput();
	TArray<TEnumAsByte<EItemType>> GetPrerequisiteItems();
	bool IsAvailable();
	AVehicleNodeActor* GetDockNode();
	bool HasPrerequisiteItems();
	bool HasPrerequisiteItem(int index);

	bool requested = false;
	UPROPERTY(VisibleAnywhere)
	bool scheduled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float productionTime = 5.0f;
	UPROPERTY(BlueprintReadWrite)
	float produceTicks = 0.0f;
private:
	UPROPERTY(EditAnywhere)
	AProductionManager* ProductionManager;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EItemType> outputItem;
	UPROPERTY(EditAnywhere)
	int32 maxInputStorage = 3;
	UPROPERTY(EditAnywhere)
	int32 maxOutputStorage = 3;
	
	UPROPERTY(EditAnywhere)
	bool unlimitedOutputStorage = false;
	UPROPERTY(EditAnywhere)
	AVehicleNodeActor* dockNode = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EItemType>> prerequisiteItems;

	
	bool isProducing = false;

	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, int32> inputItemStore;
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, int32> outputItemStore;
	UPROPERTY(VisibleAnywhere)
	TMap<TEnumAsByte<EItemType>, bool> requestedInput;

	void Produce(float DeltaTime);
	
};
