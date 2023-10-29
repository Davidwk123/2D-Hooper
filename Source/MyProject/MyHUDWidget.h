// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.generated.h"

/**
 * HudWidget will hold all Widget functionality inside HUD
 */
UCLASS()
class MYPROJECT_API UMyHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*
	* MainMenuWidget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Play;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MenuQuit;

	UFUNCTION()
	void ClickPlay();

	UFUNCTION()
	void ClickMenuQuit();

	/*
	* PawnUserWidget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* PawnUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Lives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score;

	// Widget that will provide info to the user when a certain event occurs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PawnHelp;

	void SetLives(int PawnLives);

	void SetScore(int PawnScore);

	// Will display a Text prompt that will notify user to reset the Pawn
	void SetHelp(FText PawnPrompt);

	/*
	* PauseMenuWidget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* PauseMenuWidget;

	// Canvas Widget that holds Continue and Quit Buttons 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* PausePanel;


	// Button Widget to Pause game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Pause;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Continue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseQuit;

	UFUNCTION()
	void ClickPause();

	UFUNCTION()
	void ClickContinue();

	UFUNCTION()
	void ClickPauseQuit();

	/*
	* GameOverMenuWidget
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* GameOverMenuWidget;

	// Canvas Widget that holds Play Again and Quit Buttons 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* GameOverPanel;

	// Text Widget to display Highscore
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HighScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayAgain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* GameOverQuit;

	UFUNCTION()
	void ClickPlayAgain();

	UFUNCTION()
	void ClickGameOverQuit();

protected:
	// Used to define the Dynamic when user clicks on a button
	virtual void NativeConstruct() override;
	
};
