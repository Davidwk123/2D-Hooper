// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPauseMenuWidget.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UMyPauseMenuWidget* GetPauseMenuWidget();

protected:

	// Used to add new Widget from Blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMyPauseMenuWidget> PauseMenuWidgetClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Stores new Widget from PauseMenuWidget Class
	class UMyPauseMenuWidget* PauseMenuWidget;
};
