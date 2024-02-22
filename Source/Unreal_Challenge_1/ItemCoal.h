// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemClass.h"

/**
 * 
 */
class UNREAL_CHALLENGE_1_API ItemCoal : public ItemClass
{
public:
	ItemCoal();
	virtual ItemClass* Duplicate() override;
};
