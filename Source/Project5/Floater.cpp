// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Grid.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "Math/UnrealMathUtility.h"

AFloater::AFloater() {
    static ConstructorHelpers::FObjectFinder<USoundCue> successSound(TEXT("SoundCue'/Game/Assets/Sounds/SuccessSound.SuccessSound'"));
    successSoundCue = (USoundCue*)successSound.Object;
}

bool inRange(int n, int max) {
  return n >= 0 && n < max;
}

void AFloater::BeginPlay() {
  Super::BeginPlay();
  OnActorHit.AddDynamic(this, &AFloater::onHit);
}

void AFloater::setNewPosition() {
  FVector currentLocation = this->GetActorLocation();

  FVector originalLocation = FVector(gridPos) * CELL_SIZE;

  int roundedX = FMath::RoundHalfFromZero(currentLocation.X / CELL_SIZE);
  int roundedY = FMath::RoundHalfFromZero(currentLocation.Y/ CELL_SIZE);
  int roundedZ = FMath::RoundHalfFromZero(currentLocation.Z / CELL_SIZE);

  FIntVector newGridPos = FIntVector(roundedX, roundedY, roundedZ);

  // If location is out of bounds, then snap back to original position
  if (!inRange(newGridPos.X, DEPTH)
        || !inRange(newGridPos.Y, WIDTH)) {
    this->SetActorLocation(originalLocation);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("set new position"));

    return;
  }

  // If location overlaps with another floater, then snap back to original
  if (grid->AlreadyContainsFloater(newGridPos)) {
    this->SetActorLocation(originalLocation);
    return;
  }

  // Otherwise, move the floater to its new home
  this->gridPos = newGridPos;
  this->SetActorLocation(FVector(newGridPos) * CELL_SIZE);


}

void AFloater::onHit(AActor* SelfActor, class AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
    bool isSuccess = false;
  if (OtherActor && (OtherActor != this) && OtherActor->IsA(AFaller::StaticClass())) {
    grid->floaters.erase(std::remove(grid->floaters.begin(), grid->floaters.end(), this));

    AFaller *faller = (AFaller*)OtherActor;
    if (faller->color == this->color && faller->type == this->type) {
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("YAY hit!"));
      isSuccess = true;
      HitDelegate.Execute();
    }
    else {
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NOOOOOOOOOOooooooo miss"));
    }

    grid->SpawnFloater();

    Destroy();
    OtherActor->Destroy();

    // sound effects
    UWorld* const World = GetWorld();
    if (World) {
        if (isSuccess) {
            UGameplayStatics::PlaySoundAtLocation(World, successSoundCue, GetActorLocation());
        }
    }
  }
}