// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPawnUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyPawnUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
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
	void SetHelp();

private:
	
};
