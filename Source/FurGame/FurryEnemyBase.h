// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FurryEnemyBase.generated.h"

UCLASS()
class FURGAME_API AFurryEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFurryEnemyBase();

	// Enemy health and a bool to see if enemy dies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacter)
		float health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacter)
		bool isDead{ false };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAttacking{ false };
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float currentCooldown{ .12f };
	UPROPERTY(BlueprintReadOnly)
		float attackCooldown{ .18f };
	void hitEvent(float damage, float forceScaling);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* enemyMesh;
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* collider;
	UPROPERTY(VisibleAnywhere)
		class UCharacterMovementComponent* movement;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
