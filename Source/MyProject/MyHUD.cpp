// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"

AMyHUD::AMyHUD()
{
	SetActorTickEnabled(false);

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

	AudioComponent->Stop();
}

void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Creates new Widget from HUDWidgetClass
	HUDWidget = CreateWidget<UMyHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}
