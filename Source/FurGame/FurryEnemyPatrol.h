// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FurryEnemyBase.h"
#include "FurryEnemyPatrol.generated.h"

/**
 * 
 */
UCLASS()
class FURGAME_API AFurryEnemyPatrol : public AFurryEnemyBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pathfinding)
		TArray<UObject*> Waypoints;

};
