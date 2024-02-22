// Fill out your copyright notice in the Description page of Project Settings.


#include "UC_GameModeBase.h"

#include "ProductionUserWidget.h"

void AUC_GameModeBase::BeginPlay()
{
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
