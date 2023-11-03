// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"

AMyHUD::AMyHUD()
{
	HUDWidgetClass = nullptr;
	HUDWidget = nullptr;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("UISound"));
	AudioComponent->SetupAttachment(RootComponent);
	// Enables sounds to play when game is paused
	AudioComponent->bIsUISound = true;
}

UMyHUDWidget* AMyHUD::GetHUDWidget()
{
	return HUDWidget;
}

void AMyHUD::PlayUISound()
{
	AudioComponent->Play();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	// Creates new Widget from HUDWidgetClass
	HUDWidget = CreateWidget<UMyHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();

	AudioComponent->Stop();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}
