// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSewingMachine.h"

#include "ItemLumber.h"
#include "ItemSteelBeam.h"

ItemSewingMachine::ItemSewingMachine()
{
	this->itemType = SewingMachine;
	AddPrerequisiteItem(new ItemSteelBeam());
	AddPrerequisiteItem(new ItemLumber());
}

ItemClass* ItemSewingMachine::Duplicate()
{
	return new ItemSewingMachine();
}