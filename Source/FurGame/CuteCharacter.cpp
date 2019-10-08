// Fill out your copyright notice in the Description page of Project Settings.


#include "CuteCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimInstance.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "DrawDebugHelpers.h"

// Sets default values
ACuteCharacter::ACuteCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	// set our turn rates for inputhttps://discordapp.com/channels/180752649031778305/545292570268532748
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	//Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
}

// Called when the game starts or when spawned
void ACuteCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void ACuteCharacter::OnFire()
{
	FHitResult TraceResult(ForceInit);
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	if (DoTrace(&TraceResult, &RV_TraceParams)) {
		AActor *DamagedActor = TraceResult.GetActor();
		UPrimitiveComponent *DamagedComponent = TraceResult.GetComponent();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Target: x: %s"), *DamagedActor->GetName()));

		// If we hit an actor, with a component that is simulating physics, apply an impulse  
		if ((DamagedActor != nullptr) && (DamagedActor != this) && (DamagedComponent != nullptr) && DamagedComponent->IsSimulatingPhysics())
		{
			const float ForceAmount = 40000.0f;
			FVector lineFromPlayer = DamagedActor->GetActorLocation() - GetActorLocation();
			lineFromPlayer.Normalize();
			lineFromPlayer *= ForceAmount;
			lineFromPlayer.Z *= 1.4f; // Add some extra force in the Z direction to simulate the "flying backwards and up" trope in movies when people get shot

			DamagedComponent->AddImpulse(lineFromPlayer);
		}
	}
}
bool ACuteCharacter::DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams)
{
	if (Controller == NULL) // access the controller, make sure we have one
	{
		return false;
	}

	// get the camera transform
	FVector CameraLoc;
	FRotator CameraRot;
	GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector Start = CameraLoc;
	FVector End = CameraLoc + (CameraRot.Vector() * GunRange);

	RV_TraceParams->bTraceComplex = true;
	RV_TraceParams->bReturnPhysicalMaterial = true;

	//  do the line trace
	bool DidTrace = GetWorld()->LineTraceSingleByChannel(
		*RV_Hit,        //result
		Start,        //start
		End,        //end
		ECC_Pawn,    //collision channel -- Set this to something else
		*RV_TraceParams
	);
	Start.Z -= 40.f;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f);
	return DidTrace;
}
/*
bool ACuteCharacter::DoKickTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams)
{
	if (Controller == NULL) // access the controller, make sure we have one
	{
		return false;
	}

	// get the camera transform
	FVector CameraLoc;
	FRotator CameraRot;
	GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector Start = CameraLoc;
	FVector End = CameraLoc + (CameraRot.Vector() * KickRange);

	RV_TraceParams->bTraceComplex = true;
	RV_TraceParams->bReturnPhysicalMaterial = true;

	//  do the line trace
	bool DidTrace = GetWorld()->LineTraceSingleByChannel(
		*RV_Hit,        //result
		Start,        //start
		End,        //end
		ECC_WorldStatic,    //collision channel
		*RV_TraceParams
	);
	Start.Z -= 40.f;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f);
	return DidTrace;
} */

void ACuteCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		GetCharacterMovement()->bForceMaxAccel = true;
	}
	GetCharacterMovement()->bForceMaxAccel = false;
}

void ACuteCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
		GetCharacterMovement()->bForceMaxAccel = true;
	}
	GetCharacterMovement()->bForceMaxAccel = false;
}

void ACuteCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACuteCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void ACuteCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACuteCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACuteCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ACuteCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACuteCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACuteCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACuteCharacter::LookUpAtRate);
}

