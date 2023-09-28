// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "MyInputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputDrop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* InputReset;
	
};
