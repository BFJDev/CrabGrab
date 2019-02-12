// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "TimerManager.h"
#include "Coin.h"
#include "CrabGameGameMode.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Classes/Engine/World.h"
#include "Classes/Components/BoxComponent.h"
#include "Engine.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the Box Component to represent spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

	//Initialize the coin sprite
	//CoinSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CoinSprite"));

	//Set Spawn Delay Range
	SpawnDelayRangeLow = 2.0f;
	SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		//Set the timer on spawn pickup
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	}
	else
	{
		//clear the timer on Spawn Pickup
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	//If we have set something to spawn
	if (WhatToSpawn != NULL)
	{
		//Check for valid world
		UWorld*  const World = GetWorld();
		if (World)
		{
			//Set spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Spawn pickup at random location w/ random Rotation
			FVector SpawnLocation = GetRandomPointInVolume();
			//FRotator SpawnRotation;
			//SpawnRotation.Yaw = FMath::FRand()*360.0f;
			//SpawnRotation.Pitch = FMath::FRand()*360.0f;
			//SpawnRotation.Roll = FMath::FRand()*360.0f;

			ACoin* const SpawnedPickup = World->SpawnActor<ACoin>(WhatToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
			SpawnedPickup->SetSprite2( Sprite );
			SpawnedPickup->SetSprite(Sprite);

			ACrabGameGameMode* gm = (ACrabGameGameMode*)GetWorld()->GetAuthGameMode();
			if (!(gm->GameOver))
			{
				SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
				GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
			}


		}
	}
}
