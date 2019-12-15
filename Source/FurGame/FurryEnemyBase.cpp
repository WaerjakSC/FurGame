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
	collider = GetCapsuleComponent();
	collider->InitCapsuleSize(36.f, 130.f);

	enemyMesh = GetMesh();
	bloodGush = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Blood Hit-PFX"));
	bloodGush->SetupAttachment(RootComponent);
	bloodGush->SetAutoActivate(false);

	gibs = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GIBS"));
	gibs->SetupAttachment(RootComponent);
	gibs->SetAutoActivate(false);

	enemyMesh->SetCollisionProfileName(TEXT("Ragdoll"));
	enemyMesh->SetCollisionObjectType(ECC_PhysicsBody);
	//enemyMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	enemyMesh->SetEnableGravity(true);
	enemyMesh->SetSimulatePhysics(false);

	movement = GetCharacterMovement();

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
	bloodGush->ActivateSystem();
	if (isDead) // shoot as many times as you like to spawn as many gibs as you like I guess, should be funny
	{
		gibs->ActivateSystem();
		enemyMesh->DestroyComponent();
	}
	if (health <= 0.f && !isDead)
	{
		isDead = true;
		// Disable all collision on capsule
		//collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//collider->SetCollisionResponseToAllChannels(ECR_Ignore);
		if (!bIsRagdoll) {
			collider->DestroyComponent();
			enemyMesh->SetAllBodiesSimulatePhysics(true); // Start simulating physics to active ragdoll mode.
			enemyMesh->SetSimulatePhysics(true);
			enemyMesh->WakeAllRigidBodies();
			enemyMesh->bBlendPhysics = true;

			movement->StopMovementImmediately();
			movement->DisableMovement();
			movement->SetComponentTickEnabled(false);

			bIsRagdoll = true;
			enemyMesh->SetAllPhysicsLinearVelocity(FVector(0));

		}


		// Apply force from the attack.
		FVector lineFromPlayer = -GetActorRightVector();
		lineFromPlayer *= forceScaling;
		lineFromPlayer.Z *= 1.4f; // Add some extra force in the Z direction to simulate the "flying backwards and up" trope in movies when people get shot
		enemyMesh->AddImpulse(lineFromPlayer); // Head is still too heavy so this kinda doesn't work too well atm
	}

}
