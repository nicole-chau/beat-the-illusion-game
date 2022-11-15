// Fill out your copyright notice in the Description page of Project Settings.
#include "Faller.h"

#include "Kismet/GameplayStatics.h"

#include "Grid.h"


AFaller::AFaller() {
  //PrimaryActorTick.bCanEverTick = true;
  //CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
  //  TEXT("SphereComp"));
  //CollisionComp->InitSphereRadius(0.3f);
  //CollisionComp->SetSimulatePhysics(false);
  //CollisionComp->SetEnableGravity(false);
  //CollisionComp->SetNotifyRigidBodyCollision(true);
  //CollisionComp->SetCollisionProfileName(TEXT("OverlapAll"));
  //RootComponent = CollisionComp;
  static ConstructorHelpers::FObjectFinder<USoundCue> missSound(TEXT("SoundCue'/Game/Assets/Sounds/MissSound.MissSound'"));
  missSoundCue = (USoundCue*)missSound.Object;

  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  ProjectileMovement->UpdatedComponent = mesh;
  ProjectileMovement->bInitialVelocityInLocalSpace = true;
  ProjectileMovement->bRotationFollowsVelocity = false;
  ProjectileMovement->bShouldBounce = true;
  ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AFaller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IsOffScreen();

}

void AFaller::SetSpeed(float speed) {
	ProjectileMovement->Velocity = FVector(0.0f, 0.0f, -speed);
	ProjectileMovement->InitialSpeed = speed;
	ProjectileMovement->MaxSpeed = speed;
}

void AFaller::IsOffScreen() {
	FVector currentLocation = this->GetActorLocation();
	if (currentLocation.Z < -CELL_SIZE) {
		Destroy();
    UWorld* const World = GetWorld();
    if (World) {
      UGameplayStatics::PlaySoundAtLocation(World, missSoundCue, GetActorLocation());
    }
		grid->SpawnFaller();
    grid->LoseLife();
	}
}

void AFaller::Drop() {
	float dropSpeed = 100.0f;
	ProjectileMovement->Velocity = FVector(0.0f, 0.0f, -dropSpeed);
	ProjectileMovement->InitialSpeed = dropSpeed;
	ProjectileMovement->MaxSpeed = dropSpeed;
}
