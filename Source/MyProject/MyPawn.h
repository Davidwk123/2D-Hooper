// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "MyHUDWidget.h"
#include "MyPawn.generated.h"


UCLASS()
class MYPROJECT_API AMyBasketballPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBasketballPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when user clicks and drags Pawn
	void MovePawn(const FInputActionValue& Value);

	// Called when unclicks and drops Pawn
	void DropPawn(const FInputActionValue& Value);

	// Called when user wants to reset Pawn's position
	void ResetPawn(const FInputActionValue& Value);

	void ResetPawnDefaultPosition();

	// Input Action that will call HUDWidget's ClickPause()
	void PressPause(const FInputActionValue& Value);

	// Mechanic for when user clicks and drags Pawn
	FVector GetSpringForce(FVector2d MousePosition);

	int GetPawnScore();

	// Called to reset velocity of Pawn to prevent it from clipping out of bounds
	void ResetPawnVelocity(float Drag = 0.f);
	
	// If Pawn is clicked by user
	bool IsPawnSelected();

	// If Pawn is on the ground
	bool IsPawnGrounded();

	// Adds to Score
	void PawnScored();

	// Reset Pawn's values to default 
	void ResetPawnValues();

	// Defines different cases when the Ball gets shot
	void PawnShotScenarios();

	// Called when Ball is either reset or bounces back inside Boundary
	void PawnInsideShootingBoundary();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	// Matches user input to InputActions
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere)
	class UMyInputConfigData* InputActions;

	// Stores new Widget from HUDWidget
	class UMyHUDWidget* HUDWidget;

	void SetPawnPosition(float PawnPositionX, float PawnPositionY);
	
	void CheckPawnOutOfBounds(float PawnPositionX, float PawnPositionY);

	void PawnGameOver();

	bool bIsPawnSelected;
	bool bIsPawnGrounded;
	bool bIsPawnShotValid;
	bool bDidPawnScore;
	bool bDidPawnMiss;
	bool bDidPawnRebound;

	int PawnLives;
	int PawnScore;

	const int PAWN_RADIUS = 24;
	const int RIGHT_BOUNDARY = 1065;
	const int LEFT_BOUNDARY = 23;
	const int TOP_BOUNDARY = 551;
	const int BOTTOM_BOUNDARY = -49;
	const int GROUND_HEIGHT = 36;
	const int SHOOTING_BOUNDARY = 315;
	const int STARTING_Z_POSITION = 30;
	const int STARTING_X_POSITION = 167;
	const int STARTING_Y_POSITION = 107;
	const float SPRING_CONSTANT = 500.f;
	const float DRAG_CONSTANT = 16.67f;
	const float MAX_VELOCITY = 630.f;

};
