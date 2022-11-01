// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/IntVector.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shape.generated.h"

enum ShapeType {
	CYLINDER,
	CONE,
	PRISM
};

enum ShapeColor {
	RED,
	BLUE,
	GREEN
};

UCLASS()
class PROJECT5_API AShape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShape();
	ShapeType type;
	ShapeColor color;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMesh* cylinderMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMesh* coneMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMesh* prismMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterial* redMat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterial* greenMat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterial* blueMat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void generateProperties();
};
