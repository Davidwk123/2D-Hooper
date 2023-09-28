// Fill out your copyright notice in the Description page of Project Settings.

//#include "PaperSpriteComponent.h"
#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	InputMapping = nullptr;
	InputActions = nullptr;

	bIsPawnSelected = false;
}


// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector PawnLocation = FVector(167.f, 30.f, 109.f);
	//SetActorRotation(FRotator(0.f, 0.f, 0.f));
	//SetActorLocation(PawnLocation);
	SpriteComponent->SetWorldLocation(PawnLocation);
	//UE_LOG(LogTemp, Warning, TEXT("SpriteComponent Rotation after: %s"), *SpriteComponent->GetComponentRotation().ToString());
	//SpriteComponent->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
	

	FVector NewScale = FVector(.012f, 1.f, .012f);
	SetActorScale3D(NewScale);
	SpriteComponent->SetSimulatePhysics(true);
	float SpriteMass = 0.5f;
	SpriteComponent->SetMassScale(NAME_None, SpriteMass);
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector2d PawnPosition2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), PawnPosition2d.X, PawnPosition2d.Y);*/
	//UE_LOG(LogTemp, Warning, TEXT("%f %f"),SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputActions->InputReset, ETriggerEvent::Triggered, this, &AMyPawn::MovePawn);
	PEI->BindAction(InputActions->InputReset, ETriggerEvent::Completed, this, &AMyPawn::DropPawn);
	PEI->BindAction(InputActions->InputReset, ETriggerEvent::Triggered, this, &AMyPawn::ResetPawn);
}

void AMyPawn::MovePawn(const FInputActionValue& Value)
{
	FHitResult HitResult;
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	bool bHit = MyPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	if (!bIsPawnSelected)
	{
		if (Cast<AMyPawn>(HitResult.GetActor()))
		{
			bIsPawnSelected = true;
		}
	}
	else
	{
		FVector2D MousePosition;
		MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		FVector MouseWorldLocation;
		FVector WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, MouseWorldLocation, WorldDirection);
		SpriteComponent->AddForce(GetSpringForce(FVector2d(MouseWorldLocation.X, MouseWorldLocation.Z), 500.f, 16.67));
	}
	
	//FVector PawnForce = FVector::ZeroVector;
	//if (MousePosition != FVector2d::ZeroVector)
	//{
	//	PawnForce = GetSpringForce(MousePosition, 500.f, 16.67);
	//}
	//else
	//{
	//	/*float GrabConstant = -500.f;
	//	PawnForce = FVector(GrabConstant, 0.f, 0.f);*/
	//	FVector2d PawnPosition2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	//	FVector2d BallResetPosition2d(167.f, 109.f);
	//	FVector2d BallResetDifference = BallResetPosition2d - PawnPosition2d;
	//	//int SpringConstant = 500;
	//	BallResetDifference *= 500;
	//	FVector SpringForce(BallResetDifference.X, 0.f, BallResetDifference.Y);
	//	PawnForce = SpringForce;
	//	//float DragConstant = 16.67;
	//	SpriteComponent->SetLinearDamping(16.67);

	//}

	//SpriteComponent->AddForce(PawnForce);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f"), position2d.X, position2d.Y);
}

void AMyPawn::DropPawn(const FInputActionValue& Value)
{
	bIsPawnSelected = false;
	ResetLinearDamping();
}

void AMyPawn::ResetPawn(const FInputActionValue& Value)
{
	FVector2d PawnPosition2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	int WorldLocationShootingBoundary = 340;
	int GroundHeightOfBall = 48;
	
	
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f"), PawnPosition2d.X, PawnPosition2d.Y);
	if (PawnPosition2d.X > WorldLocationShootingBoundary && PawnPosition2d.Y <= GroundHeightOfBall)
	{
		APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		FVector2D MousePosition;
		MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		FVector MouseWorldLocation;
		FVector WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, MouseWorldLocation, WorldDirection);

		if (MouseWorldLocation.X < WorldLocationShootingBoundary)
		{
			FVector PawnLocation = FVector(167.f, 30.f, 109.f);
			SpriteComponent->SetWorldLocation(PawnLocation);
			SpriteComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
			SpriteComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			//MovePawn(FVector2d(MouseWorldLocation.X, MouseWorldLocation.Z));
		}
		
	}

}

FVector AMyPawn::GetSpringForce(FVector2d MousePosition, int SpringConstant, int DragConstant)
{
	FVector2d PawnPosition2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	FVector2d MousePawnDifference2d = MousePosition - PawnPosition2d;

	//int SpringConstant = 500;
	MousePawnDifference2d *= SpringConstant;
	FVector SpringForce(MousePawnDifference2d.X, 0.f, MousePawnDifference2d.Y);

	//float DragConstant = 16.67;
	SpriteComponent->SetLinearDamping(DragConstant);

	return SpringForce;
}

void AMyPawn::ResetLinearDamping()
{
	SpriteComponent->SetLinearDamping(.01f);
	double XVelocity = SpriteComponent->GetComponentVelocity().X;
	double ZVelocity = SpriteComponent->GetComponentVelocity().Z;

	if (XVelocity > 700.f && ZVelocity > 700.f)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(700.f, 0.f, 700.f));
	}
	else if (XVelocity > 700.f)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(700.f, 0.f, ZVelocity));
	}
	else if (ZVelocity > 700.f)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(XVelocity, 0.f, 700.f));
	}
}
