// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "MyPawn.h"
#include "PaperSpriteComponent.h"


void AMyPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    this->bShowMouseCursor = true;
    //GetPawn()->GetComponentByClass<UPaperSpriteComponent>()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

void AMyPlayerController::Tick(float DeltaTime)
{

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

void AMyPlayerController::SetPawn()
{
    /*APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

    FVector2D MousePosition;
    MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

    FVector WorldLocation;
    FVector WorldDirection;
    UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, WorldLocation, WorldDirection);
    
    int WorldLocationShootingBoundary = 341;
    if (SelectedPawn == nullptr) {
        if (MyPlayerController->PlayerInput->IsPressed(EKeys::LeftMouseButton) && WorldLocation.X < WorldLocationShootingBoundary)
        {
            SelectedPawn = Cast<AMyPawn>(HitResult.GetActor());
        }
    }
    else
    {
        if (!(MyPlayerController->PlayerInput->IsPressed(EKeys::LeftMouseButton)))
        {
            SelectedPawn->ResetLinearDamping();
            SelectedPawn = nullptr;
        }
        else
        {
            if (WorldLocation.X < WorldLocationShootingBoundary)
            {
                if (SelectedPawn)
                {
                    
                    SelectedPawn->MovePawn(FVector2d(WorldLocation.X, WorldLocation.Z));
                }
            }
            else {
                UGameplayStatics::ProjectWorldToScreen(MyPlayerController, FVector(341.f, 0.f, WorldLocation.Z), MousePosition);
                SetMouseLocation(MousePosition.X, MousePosition.Y);
            }
            
        }
    }*/
}

