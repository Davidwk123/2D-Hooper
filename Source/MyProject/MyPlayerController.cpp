// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPauseMenuWidget.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();
    this->bShowMouseCursor = true;

    // Creates new Widget from PauseMenuWidgetClass
    PauseMenuWidget = CreateWidget<UMyPauseMenuWidget>(GetWorld(), PauseMenuWidgetClass);
    PauseMenuWidget->AddToViewport();
    PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AMyPlayerController::Tick(float DeltaTime)
{

}

UMyPauseMenuWidget* AMyPlayerController::GetPauseMenuWidget()
{
    return PauseMenuWidget;
}

