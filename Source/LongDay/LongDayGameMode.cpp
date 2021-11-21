// Copyright Epic Games, Inc. All Rights Reserved.

#include "LongDayGameMode.h"
#include "LongDayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALongDayGameMode::ALongDayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
