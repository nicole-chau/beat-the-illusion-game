// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

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
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < 20; ++i) {
		SpawnFloater();
	}
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool alreadyContains(const std::vector<AFloater*>& list, FIntVector gridPos) {
	for (auto& shape : list) {
		if (shape->gridPos == gridPos) {
			return true;
		}
	}
	return false;
}

void AGrid::SpawnFloater() {

	FIntVector gridPos;
	do {
		int xPos = UKismetMathLibrary::RandomInteger(DEPTH);
		int yPos = UKismetMathLibrary::RandomInteger(WIDTH);
		int zPos = UKismetMathLibrary::RandomInteger(HEIGHT);

		gridPos = FIntVector(xPos, yPos, zPos);
	} while (alreadyContains(floaters, gridPos));
	
	UWorld* const World = GetWorld();
	FVector spawnPos = FVector(gridPos) * CELL_SIZE;
	AFloater* floater = World->SpawnActor<AFloater>(AFloater::StaticClass(), spawnPos, FRotator(0.f));

	floater->gridPos = gridPos;
	floater->generateProperties();

	floaters.push_back(floater);
}
