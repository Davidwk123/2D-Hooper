// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
#include "Components/AudioComponent.h"
#include "GameFramework/GameUserSettings.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	SetActorTickEnabled(false);

	PlayerControllerClass = AMyPlayerController::StaticClass();

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundSound"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AMyProjectGameModeBase::PlayBackgroundSound()
{
	AudioComponent->SetPaused(false);
}

void AMyProjectGameModeBase::StopBackgroundSound()
{
	AudioComponent->Stop();
}

void AMyProjectGameModeBase::BeginPlay()
{
	FIntPoint ScreenResolution(SCREEN_WIDTH_X, SCREEN_WIDTH_Y);

	//Set WindowedScreen resolution
	GEngine->GameUserSettings->SetScreenResolution(ScreenResolution);
	GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);

	//Set WindowScreen dimensions
	GEngine->GameUserSettings->SetWindowPosition(SCREEN_WIDTH_X, SCREEN_WIDTH_Y);

	GEngine->GameUserSettings->ApplySettings(true);

	AudioComponent->SetPaused(true);
}
