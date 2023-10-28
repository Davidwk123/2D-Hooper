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

protected:
	// Used to add new Widget from Blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyHUDWidget> HUDWidgetClass;

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

private:
	// Stores new Widget from HUDWidgetClass
	class UMyHUDWidget* HUDWidget;
	
};
