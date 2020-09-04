// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootBulletsGameMode.h"
#include "ShootBulletsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ShootBulletsPlayerController.h"

AShootBulletsGameMode::AShootBulletsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AShootBulletsPlayerController::StaticClass();
}
