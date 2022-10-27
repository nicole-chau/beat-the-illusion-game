// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Shape.generated.h"

UENUM()
enum ShapeType {
	Cylinder UMETA(DisplayName = "Cylinder"),
	Cone UMETA(DisplayName = "Cone"),
	Prism UMETA(DisplayName = "Prism"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT5_API UShape : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ShapeType shapeType;
	FVector color;
	FTransform transform;

	UShape();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
