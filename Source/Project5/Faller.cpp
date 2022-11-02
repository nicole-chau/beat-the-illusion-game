// Fill out your copyright notice in the Description page of Project Settings.


#include "Faller.h"

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

  //ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  //ProjectileMovement->UpdatedComponent = mesh;
  //ProjectileMovement->bInitialVelocityInLocalSpace = true;
  //ProjectileMovement->InitialSpeed = 100.f;
  //ProjectileMovement->MaxSpeed = 100.f;
  //ProjectileMovement->bRotationFollowsVelocity = true;
  //ProjectileMovement->bShouldBounce = true;
  //ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AFaller::generateProperties() {
  AShape::generateProperties();
}