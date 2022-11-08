// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Floater.h"
#include "Faller.h"
#include "TimerManager.h"
#include "Shape.h"
#include "GameSpotlight.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class AFloater;

#define WIDTH 5
#define HEIGHT 5
#define DEPTH 3

#define INITIAL_NUM_FLOATERS 3

#define SPAWN_INTERVAL 10.0f

#define CELL_SIZE 8

UCLASS()
class PROJECT5_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	std::vector<AFloater*> floaters;
	std::vector<AFaller*> fallers;
	FTimerHandle fallerTimer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AFloater> FloaterClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFaller> FallerClass;

	UFUNCTION()
		void IncrementScore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 score;

	void LoseLife();

	UFUNCTION(BlueprintCallable)
		FString GetNumLivesString();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 numLives;

	float fallerSpeed;

	int maxNumFloaters;

	void ClearGrid();
	void SpawnInitialFloaters();

	int currentStreak;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnFloater();
	void SpawnFaller();
	void SpawnLight();
	bool AlreadyContainsFloater(FIntVector gridPos);
};
