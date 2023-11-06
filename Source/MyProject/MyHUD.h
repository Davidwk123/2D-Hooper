// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUDWidget.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	UMyHUDWidget* GetHUDWidget();

	void PlayUISound();

protected:
	// Used to add new Widget from Blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyHUDWidget> HUDWidgetClass;

	virtual void BeginPlay() override;
	// This function runs before BeginPlay() and the other Actors, this will allow the HUDWidget to be intialized first so that it can be refrenced by other Actors
	virtual void PostInitializeComponents() override;
	virtual void DrawHUD() override;

private:
	// Stores new Widget from HUDWidgetClass
	class UMyHUDWidget* HUDWidget;

	// UI Sound
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

};
