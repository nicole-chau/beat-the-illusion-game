// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shape.h"
#include "Faller.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT5_API AFaller : public AShape
{
	GENERATED_BODY()
public:
	FIntVector2 xyPos;
	//void generateProperties() override;
};
