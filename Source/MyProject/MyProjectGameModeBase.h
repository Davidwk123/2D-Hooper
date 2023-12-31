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

protected:
	virtual void BeginPlay() override;

private:
	// Background Sound
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

	// Other dimension that could work 954/536, 1103/617
	int SCREEN_WIDTH_X = 1103;
	int SCREEN_WIDTH_Y = 617;
};
