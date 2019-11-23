// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FurryEnemyBase.generated.h"

UCLASS()
class FURGAME_API AFurryEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFurryEnemyBase();

	// Enemy health and a bool to see if enemy dies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacter)
		float health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacter)
		bool isDead = false;

	void hitEvent(float damage, float forceScaling);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class USkeletalMeshComponent* enemyMesh;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UCapsuleComponent* collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UCharacterMovementComponent* movement;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
