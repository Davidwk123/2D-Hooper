// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "MyPawn.generated.h"




UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

//private:
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*virtual void GetMovementComponent(FVector2d mousepo) override;*/
	void PawnMovement(FVector2d mousePosition);

	void ResetLinearDamping();
};
