// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPauseMenuWidget.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    this->bShowMouseCursor = true;
}

void AMyPlayerController::Tick(float DeltaTime)
{

}

