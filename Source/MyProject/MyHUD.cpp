// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.h"
#include "Components/Button.h"

AMyHUD::AMyHUD()
{
	HUDWidgetClass = nullptr;
	HUDWidget = nullptr;
}

UMyHUDWidget* AMyHUD::GetHUDWidget()
{
	return HUDWidget;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	// Creates new Widget from MainMenuWidgetClass
	HUDWidget = CreateWidget<UMyHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}
