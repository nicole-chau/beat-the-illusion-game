// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/IntVector.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shape.generated.h"

UCLASS()
class PROJECT5_API AShape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShape();
	AShape(FIntVector position);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
