// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrabGameGameMode.generated.h"


/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of CrabGameCharacter
 */
UCLASS(minimalapi)
class ACrabGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACrabGameGameMode();

	virtual void BeginPlay() override;

	bool GameOver = false;

protected:
	/**The Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	/**The Widget class to use for end of game*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> EndGameWidgetClass;

	//Length of time the game should run
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		float GameTimeLength;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState")
	//	bool GameOver = false;

	FTimerHandle EndGameTimer;

private:

	void EndGame();

};