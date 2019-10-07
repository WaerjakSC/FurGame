// Fill out your copyright notice in the Description page of Project Settings.


#include "FurGameGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AFurGameGameModeBase::AFurGameGameModeBase() : Super(){
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/BP_MyCuteCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}