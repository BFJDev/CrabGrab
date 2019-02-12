// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CrabGameGameMode.h"
#include "CrabGameCharacter.h"
#include "Crab_Playable.h"
#include "Blueprint/UserWidget.h"
#include "Classes/Engine/World.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ACrabGameGameMode::ACrabGameGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ACrab_Playable::StaticClass();

}

void ACrabGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	//Tell the game to end in at the given time seconds
	GetWorldTimerManager().SetTimer(EndGameTimer, this, &ACrabGameGameMode::EndGame, GameTimeLength, false);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Game scheduled"));
	
}

void ACrabGameGameMode::EndGame()
{
	GameOver = true;

	//Return mouse control to player
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	MyController->bShowMouseCursor = true;

	if (EndGameWidgetClass != nullptr)
	{
		//Remove the current HUD
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->RemoveFromViewport();
		}

		//Replace it wiht the end game hud
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}