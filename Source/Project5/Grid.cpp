// Fill out your copyright notice in the Description page of Project Settings.
#include "Grid.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>
		Floater(TEXT("Blueprint'/Game/Blueprints/FloaterBP.FloaterBP'"));
	if (Floater.Object) {
		FloaterClass = (UClass*) Floater.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint>
		Faller(TEXT("Blueprint'/Game/Blueprints/FallerBP.FallerBP'"));
	if (Faller.Object) {
		FallerClass = (UClass*)Faller.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	numLives = 10;
	
	for (int i = 0; i < NUM_FLOATERS; ++i) {
		SpawnFloater();
	}

	//GetWorldTimerManager().SetTimer(fallerTimer, this, &AGrid::SpawnFaller, SPAWN_INTERVAL, true, 0.0f);
	score = 0;
	fallerSpeed = 3.5f;
	SpawnFaller();
	//SpawnLight();
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGrid::AlreadyContainsFloater(FIntVector gridPos) {
	for (auto& shape : floaters) {
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
	} while (AlreadyContainsFloater(gridPos));

	// spawn random shape and color
	int shapeTypeIdx = UKismetMathLibrary::RandomInteger(3);
	int shapeColorIdx = UKismetMathLibrary::RandomInteger(3);
	ShapeType shapeType = static_cast<ShapeType>(shapeTypeIdx);
	ShapeColor shapeColor = static_cast<ShapeColor>(shapeColorIdx);
	
	UWorld* const World = GetWorld();
	FVector spawnPos = FVector(gridPos) * CELL_SIZE;
	AFloater* floater = World->SpawnActor<AFloater>(FloaterClass, spawnPos, FRotator(0.f));

	FVector initialScale = FVector(0.01f);
	floater->SetActorScale3D(initialScale);

	floater->gridPos = gridPos;
	floater->setProperties(shapeType, shapeColor);
	floater->grid = this;

	floaters.push_back(floater);

	floater->HitDelegate.BindDynamic(this, &AGrid::IncrementScore);
}

void AGrid::SpawnFaller() {
	int xPos = UKismetMathLibrary::RandomInteger(DEPTH);
	int yPos = UKismetMathLibrary::RandomInteger(WIDTH);

	FIntVector2 xyPos(xPos, yPos);

	// spawn color that matches at least one of the floaters
	int randFloaterIdx = UKismetMathLibrary::RandomInteger(floaters.size());
	ShapeType shapeType = floaters[randFloaterIdx]->type;
	ShapeColor shapeColor = floaters[randFloaterIdx]->color;

	UWorld* const World = GetWorld();
	FVector spawnPos = FVector(xPos, yPos, HEIGHT + 1) * CELL_SIZE;
	AFaller* faller = World->SpawnActor<AFaller>(AFaller::StaticClass(), spawnPos, FRotator(0.f));

	faller->xyPos = xyPos;
	faller->setProperties(shapeType, shapeColor);
	faller->grid = this;
	faller->SetSpeed(fallerSpeed);

	// TODO: add to faller list
}

void AGrid::SpawnLight() {
	UWorld* const World = GetWorld();
	FVector spawnPos = FVector(0.0f);
	AGameSpotlight* light = World->SpawnActor<AGameSpotlight>(AGameSpotlight::StaticClass(), spawnPos, FRotator(0.f));
}


void AGrid::IncrementScore() {
	score += 10;
	if (score % 50 == 0) {
		fallerSpeed += 0.5f;
	}

	if (score % 70 == 0) {
		SpawnFloater();
	}
}

void AGrid::LoseLife() {
	numLives -= 1;
}

FString AGrid::GetNumLivesString() {
	FString res(TEXT(""));
	for (int i = 0; i < numLives; ++i) {
		res += TEXT("meow");
	}
	return res;
	//return FString(TEXT("\\u{2665}"));
}
