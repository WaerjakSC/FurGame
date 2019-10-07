// Fill out your copyright notice in the Description page of Project Settings.


#include "CuteCharacter.h"

// Sets default values
ACuteCharacter::ACuteCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACuteCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACuteCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACuteCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

