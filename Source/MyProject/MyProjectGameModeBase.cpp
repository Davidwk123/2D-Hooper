// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
#include "GameFramework/GameUserSettings.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}

void AMyProjectGameModeBase::BeginPlay()
{
	

	FIntPoint ScreenResolution(RESOLUTION_X, RESOLUTION_Y);

	//Set WindowedScreen resolution
	GEngine->GameUserSettings->SetScreenResolution(ScreenResolution);
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);

	//Set WindowScreen dimensions
	// Other dimension 954/536
	GEngine->GameUserSettings->SetWindowPosition(SCREEN_WIDTH_X, SCREEN_WIDTH_Y);

	GEngine->GameUserSettings->ApplySettings(true);


	
}
