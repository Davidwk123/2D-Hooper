// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyMainMenuWidget.h"
#include "Components/Button.h"

AMyHUD::AMyHUD()
{
	MainMenuWidgetClass = nullptr;
	MainMenuWidget = nullptr;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	// Creates new Widget from MainMenuWidgetClass
	MainMenuWidget = CreateWidget<UMyMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}
