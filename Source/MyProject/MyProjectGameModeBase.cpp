// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlayerController.h"
#include "MyCameraActor.h"
#include "MyPawn.h"
#include "MyProjectGameModeBase.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPawn::StaticClass();
}