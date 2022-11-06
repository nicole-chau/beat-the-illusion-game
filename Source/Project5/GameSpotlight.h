// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SpotLightComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSpotlight.generated.h"

UCLASS()
class PROJECT5_API AGameSpotlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSpotlight();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpotLightComponent* light;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
