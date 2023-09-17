// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MyCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCameraActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetCameraComponentPosition(FVector NewPosition);

};
