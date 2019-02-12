// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"



// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionComponent->SetSphereRadius(2, true);

	RootComponent = CollisionComponent;

	CoinSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CoinSprite"));
	CoinSprite->AttachTo(RootComponent);
	//Set Fall Speed Range
	FallSpeedRangeLow = 1.0f;
	FallSpeedRangeHigh = 2.0f;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	SetSprite(Sprite);
	FallSpeed = FMath::FRandRange(FallSpeedRangeLow, FallSpeedRangeHigh);
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0, 0, -FallSpeed));

}

void ACoin::SetSprite(UPaperSprite* NewSprite)
{
	
	CoinSprite->SetSprite(NewSprite);
}

void ACoin::SetSprite2(UPaperSprite* NewSprite)
{
	Sprite = NewSprite;
	CoinSprite->SetSprite(NewSprite);
}

