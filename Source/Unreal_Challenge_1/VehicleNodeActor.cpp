// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleNodeActor.h"

// Sets default values
AVehicleNodeActor::AVehicleNodeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
}

// Called when the game starts or when spawned
void AVehicleNodeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleNodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

