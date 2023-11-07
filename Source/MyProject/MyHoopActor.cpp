// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHoopActor.h"
#include "MyPawn.h"
#include "Components/AudioComponent.h"

// Sets default values
AMyHoopActor::AMyHoopActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(DefaultRoot);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundSound"));
	AudioComponent->SetupAttachment(RootComponent);

}

void AMyHoopActor::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AMyBasketballPawn* Ball = Cast<AMyBasketballPawn>(OtherActor);

	// When a Pawn overlaps with this Actor, PawnScore goes up by 1
	if (Ball)
	{
		Ball->PawnScored();

		AudioComponent->Play();
	}
}

// Called when the game starts or when spawned
void AMyHoopActor::BeginPlay()
{
	Super::BeginPlay();

	FVector NewScale = FVector(0.1667f, 1.f, 0.238f);
	SetActorScale3D(NewScale);

	OnActorBeginOverlap.AddDynamic(this, &AMyHoopActor::OverlapBegin);

	AudioComponent->Stop();
	
}
