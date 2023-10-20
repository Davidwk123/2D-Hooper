// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "Components/BoxComponent.h"
#include "MyTileTrigger.generated.h"

/**
 * This Actor class is the Shooting Boundary for the Pawn
 */

UCLASS()
class MYPROJECT_API AMyTileTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTileTrigger();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere)
	UPaperTileMapComponent* TileMapComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
