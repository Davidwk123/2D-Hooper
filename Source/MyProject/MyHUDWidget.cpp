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
	MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	PausePanel->SetVisibility(ESlateVisibility::Collapsed);

	// Make Pawn moveable again after user clicks Play
	Ball->GetComponentByClass<UPaperSpriteComponent>()->SetMobility(EComponentMobility::Movable);
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
#undef LOCTEXT_NAMESPACE
#endif

void UMyHUDWidget::ClickPause()
{
}

void UMyHUDWidget::ClickContinue()
{
}

void UMyHUDWidget::ClickPauseQuit()
{
}

void UMyHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Play->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickPlay);
	MenuQuit->OnClicked.AddDynamic(this, &UMyHUDWidget::ClickMenuQuit);
}
