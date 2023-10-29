// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyHUDWidget.h"
#include "MyHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    this->bShowMouseCursor = true;

    // Pauses Gameplay at the start of the Game to prevent Ball from moving 
    SetPause(true);
}

void AMyPlayerController::Tick(float DeltaTime)
{

}

void AMyPlayerController::SetupInputComponent()
{

}

