// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
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

protected:
	// Used to define the Dynamic when user clicks on a button
	virtual void NativeConstruct() override;
	
};
