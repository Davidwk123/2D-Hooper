// Fill out your copyright notice in the Description page of Project Settings.

//#include "PaperSpriteComponent.h"

#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

}

void AMyPawn::PawnMovement(FVector2d mousePosition)
{	
	FVector2d position2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	FVector2d difference2d = mousePosition - position2d;
	difference2d *=	 500;
	FVector difference(difference2d.X, 0.f, difference2d.Y);
	SpriteComponent->SetLinearDamping(16.67f);
	SpriteComponent->AddForce(difference);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), position2d.X, position2d.Y);
	
}

void AMyPawn::ResetLinearDamping()
{
	SpriteComponent->SetLinearDamping(.01f);
	if (SpriteComponent->GetComponentVelocity().X > 700.f && SpriteComponent->GetComponentVelocity().Z > 700.f)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(700.f, 0.f, 700.f));
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), SpriteComponent->GetComponentVelocity().Z);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

