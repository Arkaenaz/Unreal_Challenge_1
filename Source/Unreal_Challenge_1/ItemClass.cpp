// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemClass.h"

ItemClass::ItemClass()
{
	this->itemType = None;
}

TArray<ItemClass*> ItemClass::GetPrerequisiteItems()
{
	return this->prerequisiteItems;
}

void ItemClass::AddPrerequisiteItem(ItemClass* item)
{
	this->prerequisiteItems.Add(item);
}

void ItemClass::RemovePrerequisiteItemByIndex(int32 index)
{
	if (prerequisiteItems.IsValidIndex(index))
		this->prerequisiteItems.RemoveAt(index);
	else
		UE_LOG(LogTemp, Error, TEXT("Index is not in Range."));
}

void ItemClass::RemovePrerequisiteItemByName(FName name)
{

}

ItemClass* ItemClass::Duplicate()
{
	return new ItemClass();
}
