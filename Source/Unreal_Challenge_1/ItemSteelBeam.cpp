// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSteelBeam.h"

#include "ItemCoal.h"
#include "ItemIron.h"

ItemSteelBeam::ItemSteelBeam()
{
	this->itemType = SteelBeams;
	AddPrerequisiteItem(new ItemIron());
	AddPrerequisiteItem(new ItemCoal());
}

ItemClass* ItemSteelBeam::Duplicate()
{
	return new ItemSteelBeam();
}
