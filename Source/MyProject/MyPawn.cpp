// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"
#include "PaperTileMapActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MyPawnUserWidget.h"

// Sets default values
AMyBasketballPawn::AMyBasketballPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	InputMapping = nullptr;
	InputActions = nullptr;

	PawnWidgetClass = nullptr;
	PawnWidget = nullptr;

	bIsPawnSelected = false;

	PawnLives = 3;
	PawnScore = 0;
}


// Called when the game starts or when spawned
void AMyBasketballPawn::BeginPlay()
{
	Super::BeginPlay();
	FVector PawnLocation = FVector(167.f, 30.f, 109.f);
	SpriteComponent->SetWorldLocation(PawnLocation);
	
	FVector NewScale = FVector(.012f, 1.f, .012f);
	SetActorScale3D(NewScale);

	SpriteComponent->SetSimulatePhysics(true);
	float SpriteMass = 0.5f;
	SpriteComponent->SetMassScale(NAME_None, SpriteMass);

	PawnWidget = CreateWidget<UMyPawnUserWidget>(GetWorld(), PawnWidgetClass);
	PawnWidget->SetLives(PawnLives);
	PawnWidget->AddToViewport();
	PawnWidget->SetVisibility(ESlateVisibility::Collapsed);
	
}

void AMyBasketballPawn::SetPawnPosition(float PawnPositionX, float PawnPositionY)
{
	FVector PawnLocation = FVector(PawnPositionX, STARTING_Z_POSITION, PawnPositionY);
	SpriteComponent->SetWorldLocation(PawnLocation);
	SpriteComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
	SpriteComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

// Called every frame
void AMyBasketballPawn::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		FVector2d PawnPosition2d(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
		/*if (PawnPosition2d.X >= RightBoundary || PawnPosition2d.X <= LeftBoundary || PawnPosition2d.Y <= BottomBoundary)
		{
			FVector PawnLocation = FVector(167.f, 30.f, 109.f);
			SpriteComponent->SetWorldLocation(PawnLocation);
			SpriteComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
			SpriteComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		}*/
		/*TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors);

		for (AActor* Actor : OverlappingActors)
		{
			APaperTileMapActor* ShootingTile = Cast<APaperTileMapActor>(Actor);
			if (ShootingTile)
			{
				UE_LOG(LogTemp, Warning, TEXT("triggered"));
			}

		}*/
}

// Called to bind functionality to input
void AMyBasketballPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AMyBasketballPawn::MovePawn);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Completed, this, &AMyBasketballPawn::DropPawn);
	PEI->BindAction(InputActions->InputReset, ETriggerEvent::Triggered, this, &AMyBasketballPawn::ResetPawn);
}

void AMyBasketballPawn::MovePawn(const FInputActionValue& Value)
{
	// Stores the Actor that the mouse is hovering over
	FHitResult HitResult;
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	bool bHit = MyPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	// Get mouse screen position
	FVector2D MousePosition;
	MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	FVector MouseWorldLocation;
	FVector WorldDirection;
	// Get mouse world position
	UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, MouseWorldLocation, WorldDirection);

	if (bIsPawnSelected == false && MouseWorldLocation.X < SHOOTING_BOUNDARY)
	{
		if (Cast<AMyBasketballPawn>(HitResult.GetActor()))
		{
			bIsPawnSelected = true;
		}
	}
	else if(bIsPawnSelected && MouseWorldLocation.X > LEFT_BOUNDARY && MouseWorldLocation.X < SHOOTING_BOUNDARY)
	{
		if (MouseWorldLocation.Z <= GROUND_HEIGHT)
		{
			SetPawnPosition(MouseWorldLocation.X, GROUND_HEIGHT);
		}
		else if (MouseWorldLocation.Z >= TOP_BOUNDARY)
		{
			SetPawnPosition(MouseWorldLocation.X, TOP_BOUNDARY);
		}
		else
		{
			SpriteComponent->AddForce(GetSpringForce(FVector2d(MouseWorldLocation.X, MouseWorldLocation.Z)));
			// Called incase the Pawn's velocity gets to high 
			ResetPawnVelocity();
		}
	}
	else if(bIsPawnSelected && MouseWorldLocation.X >= SHOOTING_BOUNDARY)
	{
		if (MouseWorldLocation.Z > GROUND_HEIGHT && MouseWorldLocation.Z < TOP_BOUNDARY)
		{
			SetPawnPosition(SHOOTING_BOUNDARY, MouseWorldLocation.Z);
		}
	}
	else if(bIsPawnSelected && MouseWorldLocation.X <= LEFT_BOUNDARY)
	{
		if (MouseWorldLocation.Z > GROUND_HEIGHT && MouseWorldLocation.Z < TOP_BOUNDARY)
		{
			SetPawnPosition(LEFT_BOUNDARY, MouseWorldLocation.Z);
		}
	}
}

void AMyBasketballPawn::DropPawn(const FInputActionValue& Value)
{
	bIsPawnSelected = false;
	float DefaultDrag = 0.1f;
	ResetPawnVelocity(DefaultDrag);
}

void AMyBasketballPawn::ResetPawn(const FInputActionValue& Value)
{
	FVector2d PawnLocation2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	
	if ((PawnLocation2D.X > SHOOTING_BOUNDARY && PawnLocation2D.Y <= GROUND_HEIGHT))
	{
		SetPawnPosition(STARTING_X_POSITION, STARTING_Y_POSITION);
	}
}

FVector AMyBasketballPawn::GetSpringForce(FVector2d MousePosition)
{
	FVector2d PawnPosition2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	// Get the differnce vector between Mouse and pawn position
	FVector2d MousePawnDifference2D = MousePosition - PawnPosition2D;

	// Apply spring force to vector to create the mouse click/dragging mechanic 
	MousePawnDifference2D *= SPRING_CONSTANT;
	FVector SpringForce(MousePawnDifference2D.X, 0.f, MousePawnDifference2D.Y);
	
	// Apply new drag to match the spring constant so that the pawn does not clip out of the bounds due to the speed of the difference vector
	SpriteComponent->SetLinearDamping(DRAG_CONSTANT);

	return SpringForce;
}

UMyPawnUserWidget* AMyBasketballPawn::GetPawnWidget()
{
	return PawnWidget;
}

void AMyBasketballPawn::ResetPawnVelocity(float Drag)
{
	// Function can be called either when Pawn is unclicked by user or to check if velocity > max velcoity 
	if (Drag != 0.f)
	{
		SpriteComponent->SetLinearDamping(.01f);
	}

	float XVelocity = SpriteComponent->GetComponentVelocity().X;
	float XVelocityDir = XVelocity / abs(XVelocity);
	float YVelocity = SpriteComponent->GetComponentVelocity().Z;
	float YVelocityDir = YVelocity / abs(YVelocity);
	
	/*
	*  Checks if Pawn's X/Y velocity in any direction(absolute value is used to check this) is greater then max velocity,
	*  if so it resets either/both of them 
	*/
	if (abs(XVelocity) > MAX_VELOCITY && abs(YVelocity) > MAX_VELOCITY)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(MAX_VELOCITY * XVelocityDir, 0.f, MAX_VELOCITY * YVelocityDir));
	}
	else if (abs(XVelocity) > MAX_VELOCITY)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(MAX_VELOCITY * XVelocityDir, 0.f, YVelocity));
	}
	else if (abs(YVelocity) > MAX_VELOCITY)
	{
		SpriteComponent->SetPhysicsLinearVelocity(FVector(XVelocity, 0.f, MAX_VELOCITY * YVelocityDir));
	}
}

bool AMyBasketballPawn::IsPawnSelected()
{
	return bIsPawnSelected;
}
