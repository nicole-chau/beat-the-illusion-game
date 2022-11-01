// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

#define WIDTH 5
#define HEIGHT 5
#define DEPTH 3

#define CELL_SIZE 8

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> Shape(TEXT("Blueprint'/Game/Blueprints/ShapeBP.ShapeBP'"));
	if (Shape.Object) {
		ShapeClass = (UClass*)Shape.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < 100; ++i) {
		SpawnFloater();
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::SpawnFloater() {
	int xPos = UKismetMathLibrary::RandomInteger(DEPTH);
	int yPos = UKismetMathLibrary::RandomInteger(WIDTH);
	int zPos = UKismetMathLibrary::RandomInteger(HEIGHT);
	
	UWorld* const World = GetWorld();
	FVector spawnPos = FVector(xPos, yPos, zPos) * CELL_SIZE;
	AShape* shape = World->SpawnActor<AShape>(ShapeClass, spawnPos, FRotator(0.f));
	if (shape == nullptr) {
		GEngine->AddOnScreenDebugMessage(-3, 5.0, FColor::Green, "shape is null");
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, "SpawnFloater finished called meowmeowmeow");
}
