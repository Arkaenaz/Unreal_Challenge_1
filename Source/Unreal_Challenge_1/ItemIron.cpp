// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemIron.h"

ItemIron::ItemIron()
{
	this->itemType = Iron;
}

ItemClass* ItemIron::Duplicate()
{
	return new ItemIron();
}
