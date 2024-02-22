// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLumber.h"

ItemLumber::ItemLumber()
{
	this->itemType = Lumber;
}

ItemClass* ItemLumber::Duplicate()
{
	return new ItemLumber();
}
