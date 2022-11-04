// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SoundDefinitions.h"
#include "Sound/SoundCue.h"

#include "CoreMinimal.h"
#include "Shape.h"
#include "Floater.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDelegate);

class AGrid;

/**
 * 
 */
UCLASS()
class PROJECT5_API AFloater : public AShape
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FIntVector gridPos;
	
	AFloater();
	UFUNCTION(BlueprintCallable)
	void setNewPosition();

	UFUNCTION()
		void onHit(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		FDelegate HitDelegate;

	TSubclassOf<class AActor> Success;
	USoundCue* successSoundCue;
};
