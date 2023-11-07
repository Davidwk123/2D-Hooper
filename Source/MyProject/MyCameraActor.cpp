// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCameraActor.h"
#include "Kismet/GameplayStatics.h"


AMyCameraActor::AMyCameraActor()
{
	SetActorTickEnabled(false);
}

void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();

	ACameraActor* MyCameraActor = this;
	
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	MyPlayerController->SetViewTargetWithBlend(MyCameraActor,.0f);
}

