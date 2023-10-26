// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"
#include "PaperTileMapActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MyHUDWidget.h"
#include "MyHUD.h"

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

	HUDWidget = nullptr;

	bIsPawnSelected = false;
	bIsPawnGrounded = false;
	bDidPawnScore = false;
	bDidPawnMiss = false;
	bDidPawnRebound = false;
	bIsPawnShotValid = false;

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
	// Turn of CCD collisions to improve performance
	SpriteComponent->SetUseCCD(false);
	
	float SpriteMass = 0.5f;
	SpriteComponent->SetMassScale(NAME_None, SpriteMass);

	// Set Pawn to be unmoveable, so user can not interact with pawn in main menu screen
	SpriteComponent->SetMobility(EComponentMobility::Stationary);

	// Initialize PawnUserWidget 
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyHUD* HUD = Cast<AMyHUD>(MyPlayerController->GetHUD());
	HUDWidget = HUD->GetHUDWidget();
	HUDWidget->SetLives(PawnLives);
	HUDWidget->SetScore(PawnScore);
	// Starting PawnHelp Prompt
	HUDWidget->SetHelp(FText::FromString(TEXT("Here We Go!")));
}

void AMyBasketballPawn::SetPawnPosition(float PawnPositionX, float PawnPositionY)
{
	FVector PawnLocation = FVector(PawnPositionX, STARTING_Z_POSITION, PawnPositionY);
	SpriteComponent->SetWorldLocation(PawnLocation);
	// Sets the Pawn's Velocity/Rotation to 0 
	SpriteComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
	SpriteComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

void AMyBasketballPawn::CheckPawnOutOfBounds(float PawnPositionX, float PawnPositionY)
{
	float PawnPositionXEdge = PawnPositionX + PAWN_RADIUS;
	float PawnPositionYEdge = PawnPositionY + PAWN_RADIUS;

	if (PawnPositionXEdge <= LEFT_BOUNDARY || PawnPositionXEdge >= RIGHT_BOUNDARY || PawnPositionYEdge <= GROUND_HEIGHT)
	{
		SetPawnPosition(STARTING_X_POSITION, STARTING_Y_POSITION);
	}
}

// Called every frame
void AMyBasketballPawn::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		FVector2d PawnPosition2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
		
		CheckPawnOutOfBounds(PawnPosition2D.X, PawnPosition2D.Y);

		// Called when Pawn's velocity reaches max velocity 
		ResetPawnVelocity();

		PawnInsideShootingBoundary();

		IsPawnGrounded();

		// Check that prevents Pawn from continously losing lives
		if (bDidPawnMiss == false)
		{
			PawnShotScenarios();
		}
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
	// Check added to see if user is out of main menu screen
	if (SpriteComponent->Mobility == EComponentMobility::Movable)
	{
		// Stores the Actor that the mouse is hovering over
		FHitResult HitResult;
		APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		bool bHit = MyPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		// Get mouse screen position
		FVector2D MousePosition;
		MyPlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
		// Get mouse world position
		FVector MouseWorldLocation;
		FVector WorldDirection;
		UGameplayStatics::DeprojectScreenToWorld(MyPlayerController, MousePosition, MouseWorldLocation, WorldDirection);

		if (bIsPawnSelected == false && MouseWorldLocation.X < SHOOTING_BOUNDARY)
		{
			if (Cast<AMyBasketballPawn>(HitResult.GetActor()))
			{
				bIsPawnSelected = true;
				// When user picks up Pawn, Pawn is not grounded anymore and user can attempt a correct shoot
				bIsPawnGrounded = false;
				bIsPawnShotValid = true;
			}
		}
		else if (bIsPawnSelected && MouseWorldLocation.X > LEFT_BOUNDARY && MouseWorldLocation.X < SHOOTING_BOUNDARY)
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
			}
		}
		else if (bIsPawnSelected && MouseWorldLocation.X >= SHOOTING_BOUNDARY)
		{
			if (MouseWorldLocation.Z > GROUND_HEIGHT && MouseWorldLocation.Z < TOP_BOUNDARY)
			{
				SetPawnPosition(SHOOTING_BOUNDARY, MouseWorldLocation.Z);
				HUDWidget->SetHelp(FText::FromString(TEXT("You Can Only Shoot\nBehind the Red Line...")));
			}
		}
		else if (bIsPawnSelected && MouseWorldLocation.X <= LEFT_BOUNDARY)
		{
			if (MouseWorldLocation.Z > GROUND_HEIGHT && MouseWorldLocation.Z < TOP_BOUNDARY)
			{
				SetPawnPosition(LEFT_BOUNDARY, MouseWorldLocation.Z);
			}
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
	
	if (PawnLocation2D.X > SHOOTING_BOUNDARY && bIsPawnGrounded)
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

void AMyBasketballPawn::ResetPawnVelocity(float Drag)
{
	// This check is to see if Pawn is unclicked by user, if so reset the drag to the default value 
	if (Drag != 0.f)
	{
		SpriteComponent->SetLinearDamping(.01f);
	}

	float XVelocity = SpriteComponent->GetComponentVelocity().X;
	float YVelocity = SpriteComponent->GetComponentVelocity().Z;
	
	/*
	*  Checks if Pawn's X/Y velocity in any direction(absolute value is used to check this) is greater then max velocity,
	*  if so it sets either/both of them to max velocity 
	*/
	if (abs(XVelocity) > MAX_VELOCITY && abs(YVelocity) > MAX_VELOCITY)
	{
		float XVelocityDir = XVelocity / abs(XVelocity);
		float YVelocityDir = YVelocity / abs(YVelocity);
		SpriteComponent->SetPhysicsLinearVelocity(FVector(MAX_VELOCITY * XVelocityDir, 0.f, MAX_VELOCITY * YVelocityDir));
	}
	else if (abs(XVelocity) > MAX_VELOCITY)
	{
		float XVelocityDir = XVelocity / abs(XVelocity);
		float YVelocityDir = YVelocity / abs(YVelocity);
		SpriteComponent->SetPhysicsLinearVelocity(FVector(MAX_VELOCITY * XVelocityDir, 0.f, YVelocity));
	}
	else if (abs(YVelocity) > MAX_VELOCITY)
	{
		float XVelocityDir = XVelocity / abs(XVelocity);
		float YVelocityDir = YVelocity / abs(YVelocity);
		SpriteComponent->SetPhysicsLinearVelocity(FVector(XVelocity, 0.f, MAX_VELOCITY * YVelocityDir));
	}
}

bool AMyBasketballPawn::IsPawnSelected()
{
	return bIsPawnSelected;
}

bool AMyBasketballPawn::IsPawnGrounded()
{
	FVector2d PawnLocation2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);

	if (PawnLocation2D.Y <= GROUND_HEIGHT && bIsPawnSelected == false)
	{
		bIsPawnGrounded = true;
	}

	return bIsPawnGrounded;
}

void AMyBasketballPawn::PawnScored()
{
	bDidPawnScore = true;
	PawnScore++;
	HUDWidget->SetScore(PawnScore);
	HUDWidget->SetHelp(FText::FromString(TEXT("Nice Shot!")));
}

void AMyBasketballPawn::PawnShotScenarios()
{
	FVector2d PawnLocation2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);
	
	// Pawn's Radius is subtracted from Pawn location to prevent Pawn from losing a life if Pawn is on the Shooting Boundary 
	if (PawnLocation2D.X - PAWN_RADIUS > SHOOTING_BOUNDARY && bIsPawnGrounded && bIsPawnShotValid && bDidPawnScore == false)
	{
		bDidPawnMiss = true;
		PawnLives--;
		HUDWidget->SetLives(PawnLives);
		bDidPawnRebound = false;
		// Show PawnHelp Text prompt when ball is misses
		HUDWidget->SetHelp(FText::FromString(TEXT("Nice Try!\n\nClick on Screen to Reset Ball...")));
	}
	// Check for when Ball rebounds off the Wall/Hoop
	else if (PawnLocation2D.X - PAWN_RADIUS > SHOOTING_BOUNDARY && bIsPawnGrounded == false && bIsPawnShotValid && bDidPawnScore == false)
	{
		bDidPawnRebound = true;
		HUDWidget->SetHelp(FText::FromString(TEXT("Shot is Up...")));
	}
	// Display PawnHelp Text prompt in case shot is not valid 
	else if(PawnLocation2D.X - PAWN_RADIUS > SHOOTING_BOUNDARY && bIsPawnGrounded && bDidPawnScore == false)
	{
		HUDWidget->SetHelp(FText::FromString(TEXT("Oops!\n\nClick on Screen to Reset Ball...")));
	}
	// Display PawnHelp Text Prompt if Pawn scores 
	else if (bIsPawnGrounded && bDidPawnScore)
	{
		bDidPawnRebound = false;
		// Show PawnHelp Text prompt when ball is Score
		HUDWidget->SetHelp(FText::FromString(TEXT("Nice Shot!\n\nClick on Screen to Reset Ball...")));
	}
}

void AMyBasketballPawn::PawnInsideShootingBoundary()
{
	FVector2d PawnLocation2D(SpriteComponent->GetComponentLocation().X, SpriteComponent->GetComponentLocation().Z);

	if (PawnLocation2D.X <= SHOOTING_BOUNDARY)
	{
		// Checks for when Ball rebounds off the Wall/Hoop and makes it back to the Shooting Boundary
		if (bDidPawnRebound && bDidPawnScore == false && bIsPawnGrounded)
		{
			PawnLives--;
			HUDWidget->SetLives(PawnLives);
			bDidPawnRebound = false;
			HUDWidget->SetHelp(FText::FromString(TEXT("Unlucky Rebound!")));
		}
		// Case where user Catches the Rebound and does not lose a Life
		else if(bDidPawnRebound && bDidPawnScore == false && bIsPawnSelected == true)
		{
			bDidPawnRebound = false;
			HUDWidget->SetHelp(FText::FromString(TEXT("Nice Catch!\n\nTake Another Shot!")));
		}

		// Checks if user's shot is not valid 
		if (bIsPawnGrounded)
		{
			bIsPawnShotValid = false;
			HUDWidget->SetHelp(FText::FromString(TEXT("Pick Up Ball to Shoot...")));
		}

		// Resets the check for when user misses/makes/rebounds the shot 
		bDidPawnMiss = false;
		bDidPawnScore = false;
	}

}
