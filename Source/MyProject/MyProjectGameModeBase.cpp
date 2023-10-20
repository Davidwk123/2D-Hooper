// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}