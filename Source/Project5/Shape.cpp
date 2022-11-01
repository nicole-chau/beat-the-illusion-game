// Fill out your copyright notice in the Description page of Project Settings.

#include "Shape.h"
#include "Engine/StaticMesh.h"

#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

// Sets default values
AShape::AShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	//SetRootComponent(mesh);
	mesh->SetupAttachment(GetRootComponent());
	//mesh->SetSimulatePhysics(true);
	//mesh->SetNotifyRigidBodyCollision(true);

	cylinderMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("cylinderMesh"));
	prismMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("prismMesh"));
	coneMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("coneMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(TEXT("StaticMesh'/Game/Assets/cone.cone'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("StaticMesh'/Game/Assets/cylinder.cylinder'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PrismAsset(TEXT("StaticMesh'/Game/Assets/prism.prism'"));

	cylinderMesh = CylinderAsset.Object;
	prismMesh = PrismAsset.Object;
	coneMesh = ConeAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> RedAsset
		(TEXT("Material'/Game/Materials/RedMaterial.RedMaterial'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> BlueAsset
		(TEXT("Material'/Game/Materials/BlueMaterial.BlueMaterial'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> GreenAsset
		(TEXT("Material'/Game/Materials/GreenMaterial.GreenMaterial'"));

	redMat = RedAsset.Object;
	blueMat = BlueAsset.Object;
	greenMat = GreenAsset.Object;
}

// Called when the game starts or when spawned
void AShape::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShape::generateProperties() {
	int shapeType = UKismetMathLibrary::RandomInteger(3);
	type = static_cast<ShapeType>(shapeType);

	switch (type) {
	case PRISM:
		mesh->SetStaticMesh(prismMesh);
		break;
	case CYLINDER:
		mesh->SetStaticMesh(cylinderMesh);
		break;
	case CONE:
		mesh->SetStaticMesh(coneMesh);
		break;
	}

	int colorRand = UKismetMathLibrary::RandomInteger(3);
	color = static_cast<ShapeColor>(colorRand);

	switch (color) {
	case RED:
		mesh->SetMaterial(0, redMat);
		break;
	case BLUE:
		mesh->SetMaterial(0, blueMat);
		break;
	case GREEN:
		mesh->SetMaterial(0, greenMat);
		break;
	}

	//mesh->AttachParent = RootComponent;
	mesh->SetRelativeScale3D(FVector(2, 2, 2));

	// Generate random orientation about the z-axis
	FVector axisVector = FVector(0, 0, 1);
	int orientation = UKismetMathLibrary::RandomInteger(4);

	FQuat rotation(axisVector, PI / 2 * orientation);
	mesh->SetRelativeRotation(rotation);
}
