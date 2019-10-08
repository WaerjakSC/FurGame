// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CuteCharacter.generated.h"

UCLASS()
class FURGAME_API ACuteCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACuteCharacter();
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Fires a projectile. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "On Player Fire"))
		void OnFire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnFireInternal();

	bool DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);
	bool DoKickTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Character health.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacter)
		float characterHealth = 100;

	// Is the character alive or not?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacter)
		bool isDead = false;

	// Is the glock or the shotgun selected?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerCharacter)
		bool glockSelected = true;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffset;
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	// Range of the line trace for gun, shotgun and kick attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float GunRange{ 2500.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShotgunRange{ 1000.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float KickRange{ 80.f };

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

};
