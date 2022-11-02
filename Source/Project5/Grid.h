// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Floater.h"
#include "Faller.h"
#include "TimerManager.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnFloater();
	void SpawnFaller();
};
