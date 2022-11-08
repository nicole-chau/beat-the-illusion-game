// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Grid.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "Math/UnrealMathUtility.h"

AFloater::AFloater() {
    static ConstructorHelpers::FObjectFinder<USoundCue> successSound(TEXT("SoundCue'/Game/Assets/Sounds/SuccessSound.SuccessSound'"));
    successSoundCue = (USoundCue*)successSound.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue> failureSound(TEXT("SoundCue'/Game/Assets/Sounds/FailureSound.FailureSound'"));
    failureSoundCue = (USoundCue*)failureSound.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue> alternateSuccessSound(TEXT("SoundCue'/Game/Assets/Sounds/AlternateSuccessSound.AlternateSuccessSound'"));
    alternateSuccessSoundCue = (USoundCue*)alternateSuccessSound.Object;

    static ConstructorHelpers::FObjectFinder<USoundCue> spawnSound(TEXT("SoundCue'/Game/Assets/Sounds/SpawnSound.SpawnSound'"));
    spawnSoundCue = (USoundCue*)spawnSound.Object;
}

bool inRange(int n, int max) {
  return n >= 0 && n < max;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  FVector scale = this->GetActorScale3D();
  if (scale.X >= 1.0f) {
    return;
  }

  FVector newScale = scale + 6.5 * DeltaTime * scale;
  if (newScale.X > 1.0f) { // don't let final scale exceed 1, ever
    newScale = FVector(1.0f);
  }
  this->SetActorScale3D(newScale);
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
      //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("YAY hit!"));
      isSuccess = true;
      grid->currentStreak++;
      if (grid->currentStreak % 3 == 0) {
        grid->ClearGrid();
        grid->SpawnInitialFloaters();
      }
      HitDelegate.Execute();
    }
    else {
      grid->LoseLife();
      grid->currentStreak = 0;
      //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NOOOOOOOOOOooooooo miss"));
    }

    grid->SpawnFloater();
    grid->SpawnFaller();

    if (grid->floaters.size() < grid->maxNumFloaters) {
      grid->SpawnFloater();
    }

    Destroy();
    OtherActor->Destroy();

    // sound effects
    UWorld* const World = GetWorld();
    if (World) {
        if (isSuccess) {
          if (grid->score % 150 == 0) {
            // "Oh yes daddy"
            UGameplayStatics::PlaySoundAtLocation(World, alternateSuccessSoundCue, GetActorLocation());
          }
          else {
            UGameplayStatics::PlaySoundAtLocation(World, successSoundCue, GetActorLocation());
          }
        }
        else {
            UGameplayStatics::PlaySoundAtLocation(World, failureSoundCue, GetActorLocation());

        }
    }
  }
}

void AFloater::PlaySpawnSound() {
  UWorld* const World = GetWorld();
  if (World) {
    UGameplayStatics::PlaySoundAtLocation(World, spawnSoundCue, GetActorLocation());
  }
}
