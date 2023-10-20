// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Play;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Quit;

	UFUNCTION()
	void ClickPlay();

	UFUNCTION()
	void ClickQuit();

protected:
	// Used to define the Dynamic when user clicks on a button
	virtual void NativeConstruct() override;
};
