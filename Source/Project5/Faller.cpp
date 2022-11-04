// Fill out your copyright notice in the Description page of Project Settings.


#include "Faller.h"
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
	if (currentLocation.Z < -13) {
		Destroy();
		grid->SpawnFaller();
	}
}
