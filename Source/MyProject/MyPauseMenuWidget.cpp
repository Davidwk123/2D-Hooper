// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawn.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyPauseMenuWidget::ClickPause()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	// Freezes everything in World
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	// Make Pawn moveable again after user clicks Play
	//Ball->GetComponentByClass<UPaperSpriteComponent>()->SetMobility(EComponentMobility::Stationary);

}

void UMyPauseMenuWidget::ClickContinue()
{
}

void UMyPauseMenuWidget::ClickQuit()
{
}

void UMyPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Pause->OnClicked.AddDynamic(this, &UMyPauseMenuWidget::ClickPause);
	Continue->OnClicked.AddDynamic(this, &UMyPauseMenuWidget::ClickContinue);
	Quit->OnClicked.AddDynamic(this, &UMyPauseMenuWidget::ClickQuit);
}
