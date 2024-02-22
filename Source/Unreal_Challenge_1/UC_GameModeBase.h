// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UC_GameModeBase.generated.h"

class UProductionUserWidget;
/**
 * 
 */
UCLASS()
class UNREAL_CHALLENGE_1_API AUC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	UProductionUserWidget* GameWidget;

	virtual void BeginPlay() override;
};
