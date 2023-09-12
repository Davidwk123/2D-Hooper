// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    PlayerController->bShowMouseCursor = true;

}

void AMyPlayerController::Tick(float DeltaTime)
{
    FVector2D MousePosition;
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0); 
   
    if (PlayerController)
    {
        PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

        UE_LOG(LogTemp, Warning, TEXT("Mouse X: %f, Mouse Y: %f"), MousePosition.X, MousePosition.Y);
    }
}