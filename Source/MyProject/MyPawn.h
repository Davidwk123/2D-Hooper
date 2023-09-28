// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "InputActionValue.h"
#include "MyPawn.generated.h"





UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void GetMovementComponent(FVector2d mousepo) override;
	
	void MovePawn(const FInputActionValue& Value);

	void DropPawn(const FInputActionValue& Value);

	void ResetPawn(const FInputActionValue& Value);

	FVector GetSpringForce(FVector2d MousePosition, int SpringConstant, int DragConstant);

	void ResetLinearDamping();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere)
	class UMyInputConfigData* InputActions;

	bool bIsPawnSelected;

};
