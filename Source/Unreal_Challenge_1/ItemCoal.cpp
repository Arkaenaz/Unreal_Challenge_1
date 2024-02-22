// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCoal.h"

ItemCoal::ItemCoal()
{
	this->itemType = Coal;
}

ItemClass* ItemCoal::Duplicate()
{
	return new ItemCoal();
}
