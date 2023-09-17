// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "MyPawn.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    this->bShowMouseCursor = true;

}

void AMyPlayerController::setPawn()
{
    APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

    FVector2D MousePosition;
    MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, WorldLocation, WorldDirection);

    if (selectedPawn == nullptr) {
        if (MyPlayerController->PlayerInput->IsPressed(EKeys::LeftMouseButton))
        {
            selectedPawn = Cast<AMyPawn>(HitResult.GetActor());
        }
    }
    else
    {
        if (!(MyPlayerController->PlayerInput->IsPressed(EKeys::LeftMouseButton)))
        {
            selectedPawn->ResetLinearDamping();
            selectedPawn = nullptr;
        }
        else
        {
            if (selectedPawn)
            {
                selectedPawn->PawnMovement(FVector2d(WorldLocation.X, WorldLocation.Z));
            }
            
        }
    }
}

void AMyPlayerController::Tick(float DeltaTime)
{
    setPawn();

   // FVector2D MousePosition;
   // APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
   // MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    /*UE_LOG(LogTemp, Warning, TEXT("%f"),DeltaTime);*/

   // if (MyPlayerController->PlayerInput->IsPressed(EKeys::LeftMouseButton))
   // {
   //    
   //     FHitResult HitResult;
   //     GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

   //     AMyPawn* ClickedPawn = Cast<AMyPawn>(HitResult.GetActor());

   //     if(ClickedPawn)
   //     {

   //         // Trigger the event on the clicked pawn
   //         ClickedPawn->PawnMovement(MousePosition);
   //         /*UE_LOG(LogTemp, Warning, TEXT("Clicked"));*/
   //        
   //     }
   // }
}