// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

AMyCameraActor::AMyCameraActor()
{
	
}

void AMyCameraActor::BeginPlay()
{
	Super::BeginPlay();
	FTransform transform(FRotator{ .0f, -90.0f, .0f }, FVector{ 512.0f, 512.0f, 288.0f }, FVector{ 1.0f, 1.0f, 1.0f });
	ACameraActor* MyCameraActor = this;
	MyCameraActor->SetActorTransform(transform);
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	MyPlayerController->SetViewTargetWithBlend(MyCameraActor,.0f);
	
}

void AMyCameraActor::SetCameraComponentPosition(FVector NewPosition)
{
	
	
  
}