// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductionManager.h"

/**
 * 
 */
class UNREAL_CHALLENGE_1_API ItemClass
{
public:
	ItemClass();

	TEnumAsByte<EItemType> itemType;
	TArray<ItemClass*> GetPrerequisiteItems();
	void AddPrerequisiteItem(ItemClass* item);
	void RemovePrerequisiteItemByIndex(int32 index);
	void RemovePrerequisiteItemByName(FName name);
	virtual ItemClass* Duplicate();

protected:
	TArray<ItemClass*> prerequisiteItems;
};
