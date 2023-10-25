// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMyMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UMyMainMenuWidget::ClickPlay);
	Quit->OnClicked.AddDynamic(this, &UMyMainMenuWidget::ClickQuit);
}

void UMyMainMenuWidget::ClickPlay()
{
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());
	
	// Hide MainMenu Widget and Display Pause/Pawn Widgets
	SetVisibility(ESlateVisibility::Collapsed);
	MyPlayerController->GetPauseMenuWidget()->SetVisibility(ESlateVisibility::Visible);
	Ball->GetPawnWidget()->SetVisibility(ESlateVisibility::Visible);
	
	// Make Pawn moveable again after user clicks Play
	Ball->GetComponentByClass<UPaperSpriteComponent>()->SetMobility(EComponentMobility::Movable);
}

void UMyMainMenuWidget::ClickQuit()
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(this, 0), QuitPreference, true);
}
