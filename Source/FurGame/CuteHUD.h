// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CuteHUD.generated.h"

/**
 * 
 */
UCLASS()
class FURGAME_API ACuteHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACuteHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};
