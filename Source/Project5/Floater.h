// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shape.h"
#include "Floater.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT5_API AFloater : public AShape
{
	GENERATED_BODY()
	
public:
	FIntVector gridPos;

};
