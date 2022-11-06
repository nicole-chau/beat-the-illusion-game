// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSpotlight.h"

// Sets default values
AGameSpotlight::AGameSpotlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	light->SetupAttachment(RootComponent);
	light->SetLightColor(FLinearColor(1.0f, 0.0f, 0.0f));
	light->SetWorldLocation(FVector(-10.0f, 20.0f, 15.0f));
	light->SetWorldRotation(FQuat::MakeFromEuler(FVector(-90.0f, 0.0f, 0.0f)));
}

// Called when the game starts or when spawned
void AGameSpotlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSpotlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

