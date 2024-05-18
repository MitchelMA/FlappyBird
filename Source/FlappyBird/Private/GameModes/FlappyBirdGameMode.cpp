// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/FlappyBirdGameMode.h"
#include "UObject/ConstructorHelpers.h"

AFlappyBirdGameMode::AFlappyBirdGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/FlappyBird/Blueprints/BP_BirdCharacter"));
	if (PlayerPawnBPClass.Class)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}
