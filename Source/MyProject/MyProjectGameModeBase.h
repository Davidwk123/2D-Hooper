// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameModeBase();

	void PlayBackgroundSound();

	void StopBackgroundSound();

protected:
	virtual void BeginPlay() override;

private:
	// Background Sound
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

	int RESOLUTION_X = 1920;
	int RESOLUTION_Y = 1080;
	int SCREEN_WIDTH_X = 1024;
	int SCREEN_WIDTH_Y = 576;
};
