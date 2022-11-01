// Fill out your copyright notice in the Description page of Project Settings.

#include "Shape.h"
#include "Engine/StaticMesh.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AShape::AShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(mesh);
	//mesh->SetupAttachment(GetRootComponent());

	cylinderMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("cylinderMesh"));
	prismMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("prismMesh"));
	coneMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("coneMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("StaticMesh'/Game/Assets/cylinder.cylinder'"));

	//if (!CylinderAsset.Succeeded()) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "nullinder finished meowmeowmeow");
	//}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PrismAsset(TEXT("StaticMesh/'Game/Assets/prism.prism'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(TEXT("StaticMesh'/Game/Assets/cone.cone'"));

	cylinderMesh = CylinderAsset.Object;
	prismMesh = PrismAsset.Object;
	coneMesh = ConeAsset.Object;
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

	if (cylinderMesh == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "nullinder finished meowmeowmeow");
	}

	switch (type) {
	case CYLINDER:
		mesh->SetStaticMesh(cylinderMesh);
		break;
	case PRISM:
		mesh->SetStaticMesh(prismMesh);
		break;
	case CONE:
		mesh->SetStaticMesh(coneMesh);
		break;
	}

	int colorRand = UKismetMathLibrary::RandomInteger(3);
	color = static_cast<ShapeColor>(colorRand);

	//RedMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>
	//	(TEXT("Material/'Game/Materials/RedMaterial.RedMaterial'"));
	//BlueMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>
	//	(TEXT("Material'/Game/Materials/BlueMaterial.BlueMaterial'"));
	//GreenMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>
	//	(TEXT("Material/'Game/Materials/GreenMaterial.GreenMaterial'"));

	//switch (color) {
	//case RED:
	//	mesh->SetMaterial(0, RedMaterial.Object);
	//	break;
	//case BLUE:
	//	mesh->SetMaterial(0, BlueMaterial.Object);
	//	break;
	//case GREEN:
	//	mesh->SetMaterial(0, GreenMaterial.Object);
	//	break;
	//}

	//mesh->AttachParent = RootComponent;
	mesh->SetRelativeScale3D(FVector(2, 2, 2));
}
