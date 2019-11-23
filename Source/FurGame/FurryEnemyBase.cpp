// Fill out your copyright notice in the Description page of Project Settings.


#include "FurryEnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
AFurryEnemyBase::AFurryEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = collider;
	collider->InitCapsuleSize(36.f, 130.f);
	collider->SetCollisionProfileName(TEXT("Pawn"));

	enemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	enemyMesh->SetupAttachment(RootComponent);

	enemyMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	enemyMesh->SetEnableGravity(true);
	enemyMesh->SetSimulatePhysics(false);
	enemyMesh->RelativeLocation = FVector(0.f, 0.f, -125.f);



	//movement = CreateAbstractDefaultSubobject<UCharacterMovementComponent>(TEXT("Movement"));

}

// Called when the game starts or when spawned
void AFurryEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFurryEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFurryEnemyBase::hitEvent(float damage, float forceScaling)
{
	health -= damage;

	if (health <= 0.f)
	{
		isDead = true;
		collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		enemyMesh->SetSimulatePhysics(true);
		FVector lineFromPlayer = -GetActorForwardVector();
		lineFromPlayer *= forceScaling;
		lineFromPlayer.Z *= 1.4f; // Add some extra force in the Z direction to simulate the "flying backwards and up" trope in movies when people get shot
		enemyMesh->AddImpulse(lineFromPlayer);
	}
}
