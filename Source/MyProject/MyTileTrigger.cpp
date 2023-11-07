// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTileTrigger.h"
#include "PaperTileMapComponent.h"
#include "MyPawn.h"

// Sets default values
AMyTileTrigger::AMyTileTrigger()
{

	SetActorTickEnabled(false);

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(DefaultRoot);

	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));
	TileMapComponent->SetupAttachment(DefaultRoot);
}

// Called when the game starts or when spawned
void AMyTileTrigger::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorHiddenInGame(true);
	// Adds the dynamics for when an Actor overlaps this Actor 
	OnActorBeginOverlap.AddDynamic(this, &AMyTileTrigger::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyTileTrigger::OverlapEnd);
	
}

void AMyTileTrigger::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(OtherActor);

	// When a Pawn overlaps with this Actor, this Actor is shown in the world 
	if (Ball && Ball->IsPawnSelected())
	{
		this->SetActorHiddenInGame(false);
	}
}

void AMyTileTrigger::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(OtherActor);

	// When a Pawn overlap ends with this Actor, this Actor is hidden in the world 
	if (Ball)
	{
		this->SetActorHiddenInGame(true);
	}
}

