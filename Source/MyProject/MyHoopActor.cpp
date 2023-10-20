// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHoopActor.h"

// Sets default values
AMyHoopActor::AMyHoopActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(DefaultRoot);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(DefaultRoot);

}

void AMyHoopActor::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
}

void AMyHoopActor::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
}

// Called when the game starts or when spawned
void AMyHoopActor::BeginPlay()
{
	Super::BeginPlay();

	FVector NewScale = FVector(0.1667f, 1.f, 0.238f);
	SetActorScale3D(NewScale);

	OnActorBeginOverlap.AddDynamic(this, &AMyHoopActor::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyHoopActor::OverlapEnd);
	
}

// Called every frame
void AMyHoopActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
