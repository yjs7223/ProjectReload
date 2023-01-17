// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectReloadGameMode.h"
#include "ProjectReloadCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectReloadGameMode::AProjectReloadGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
