// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoorSystemMassGameMode.h"
#include "DoorSystemMassHUD.h"
#include "DoorSystemMassCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADoorSystemMassGameMode::ADoorSystemMassGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADoorSystemMassHUD::StaticClass();
}
