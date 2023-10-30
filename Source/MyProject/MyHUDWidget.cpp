// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUDWidget.h"
#include "MyPlayerController.h"
#include "MyPawn.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMyHUDWidget::ClickPlay()
{
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	// Hide MainMenuWidget and Display Pause/Pawn Widgets
	PausePanel->SetVisibility(ESlateVisibility::Collapsed);

	GameOverPanel->SetVisibility(ESlateVisibility::Collapsed);

	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	// Unpause game and make pawn moveable again after user clicks Play, also prevents user from pressing Pause during Main Menu screen
	Ball->GetComponentByClass<UPaperSpriteComponent>()->SetMobility(EComponentMobility::Movable);
	MyPlayerController->SetPause(false);
}

void UMyHUDWidget::ClickMenuQuit()
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(this, 0), QuitPreference, true);
}

// The "if" and "define" allows the use of the "LOCTEXT" in the functions, which allow int values to be used with string values 
#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "UMG"
void UMyHUDWidget::SetLives(int PawnLives)
{
	if (Lives)
	{
		Lives->SetText(FText::Format(LOCTEXT("CombinedTextKey", "Lives: {0}"), PawnLives));
	}
}

void UMyHUDWidget::SetScore(int PawnScore)
{
	if (Score)
	{
		Score->SetText(FText::Format(LOCTEXT("CombinedTextKey", "Score: {0}"), PawnScore));
	}
}

void UMyHUDWidget::SetHelp(FText PawnPrompt)
{
	if (PawnHelp)
	{
		PawnHelp->SetText(PawnPrompt);
	}
}

void UMyHUDWidget::SetHighScore(int PawnScore)
{
	if (HighScore)
	{
		HighScore->SetText(FText::Format(LOCTEXT("CombinedTextKey", "\tScore: {0}"), PawnScore));
	}
}

#undef LOCTEXT_NAMESPACE
#endif

void UMyHUDWidget::ClickPause()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	// Freezes everything in World
	MyPlayerController->SetPause(true);

	PausePanel->SetVisibility(ESlateVisibility::Visible);

	PawnHelp->SetVisibility(ESlateVisibility::Hidden);
}

void UMyHUDWidget::ClickContinue()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	// Unfreezes everything in World
	MyPlayerController->SetPause(false);

	PawnHelp->SetVisibility(ESlateVisibility::Visible);

	PausePanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMyHUDWidget::ClickPauseQuit()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	PawnUserWidget->SetVisibility(ESlateVisibility::Hidden);

	PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);

	GameOverPanel->SetVisibility(ESlateVisibility::Visible);

	SetHighScore(Ball->GetPawnScore());
}

void UMyHUDWidget::ClickPlayAgain()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	PawnUserWidget->SetVisibility(ESlateVisibility::Visible);
	PawnHelp->SetVisibility(ESlateVisibility::Visible);

	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	PausePanel->SetVisibility(ESlateVisibility::Hidden);

	GameOverPanel->SetVisibility(ESlateVisibility::Hidden);

	Ball->ResetPawnDefaultPosition();
	Ball->ResetPawnValues();
	MyPlayerController->SetPause(false);
}

void UMyHUDWidget::ClickGameOverQuit()
{
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(MyPlayerController->GetPawn());

	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);

	PawnUserWidget->SetVisibility(ESlateVisibility::Visible);
	PawnHelp->SetVisibility(ESlateVisibility::Visible);

	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	PausePanel->SetVisibility(ESlateVisibility::Hidden);

	GameOverPanel->SetVisibility(ESlateVisibility::Hidden);

	Ball->ResetPawnDefaultPosition();
	Ball->ResetPawnValues();
	Ball->GetComponentByClass<UPaperSpriteComponent>()->SetMobility(EComponentMobility::Stationary);
	MyPlayerController->SetPause(false);
}

void UMyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Play->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickPlay);
	MenuQuit->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickMenuQuit);

	Pause->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickPause);
	Continue->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickContinue);
	PauseQuit->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickPauseQuit);

	PlayAgain->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickPlayAgain);
	GameOverQuit->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickGameOverQuit);
}
