// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyHUDWidget.h"
#include "MyHUD.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"

AMyPlayerController::AMyPlayerController()
{
    SetActorTickEnabled(false);
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    this->bShowMouseCursor = true;
}
